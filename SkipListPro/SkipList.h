// SkipList.h
#ifndef SKIPLISTPRO_SKIPLIST_H
#define SKIPLISTPRO_SKIPLIST_H

#include <cstddef>
#include <cassert>
#include <ctime>
#include <mutex>
#include "Node.h"
#include "MemoryPool.h"

// 跳表类
template<typename K, typename V>
class SkipList {
public:
    // 构造函数，初始化跳表，设置尾部键和随机数种子，并创建内存池
    SkipList(K footerKey) : rnd(0x12345678), memoryPool(100) {
        createList(footerKey);
    }

    // 析构函数，释放跳表的内存
    ~SkipList() {
        freeList();
    }

    // 查找指定键的节点
    Node<K, V> *search(K key) const;

    // 插入键值对
    bool insert(K key, V value);

    // 删除指定键的节点，并返回其值
    bool remove(K key, V &value);

    // 获取跳表中元素的数量
    int size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return nodeCount;
    }

    // 获取跳表的层级
    int getLevel() const {
        std::lock_guard<std::mutex> lock(mtx);
        return level;
    }

private:
    // 创建跳表
    void createList(K footerKey);
    // 释放跳表的内存
    void freeList();
    // 创建指定层级的节点
    void createNode(int level, Node<K, V> *&node);
    // 创建指定层级的节点，并初始化其键和值
    void createNode(int level, Node<K, V> *&node, K key, V value);
    // 获取随机层级
    int getRandomLevel();
    // 打印所有节点信息
    void dumpAllNodes();
    // 打印节点详细信息
    void dumpNodeDetail(Node<K, V> *node, int nodeLevel);

private:
    int level;  // 跳表的层级
    Node<K, V> *header;  // 跳表的头节点
    Node<K, V> *footer;  // 跳表的尾节点
    size_t nodeCount;  // 跳表中节点的数量
    static const int MAX_LEVEL = 16;  // 跳表的最大层级
    MemoryPool<Node<K, V>> memoryPool;  // 内存池
    mutable std::mutex mtx;  // 互斥锁，用于多线程安全
    unsigned int rnd;  // 添加 rnd 成员变量
};

// 创建跳表
template<typename K, typename V>
void SkipList<K, V>::createList(K footerKey) {
    createNode(0, footer);
    footer->key = footerKey;
    this->level = 0;
    createNode(MAX_LEVEL, header);
    for (int i = 0; i < MAX_LEVEL; ++i) {
        header->forward[i] = footer;
    }
    nodeCount = 0;
}

// 创建指定层级的节点
template<typename K, typename V>
void SkipList<K, V>::createNode(int level, Node<K, V> *&node) {
    node = memoryPool.allocate();
    node->forward = new Node<K, V> *[level + 1];
    node->nodeLevel = level;
    assert(node != nullptr);
}

// 创建指定层级的节点，并初始化其键和值
template<typename K, typename V>
void SkipList<K, V>::createNode(int level, Node<K, V> *&node, K key, V value) {
    node = memoryPool.allocate();
    node->key = key;
    node->value = value;
    if (level > 0) {
        node->forward = new Node<K, V> *[level + 1];
    }
    node->nodeLevel = level;
    assert(node != nullptr);
}

// 释放跳表的内存
template<typename K, typename V>
void SkipList<K, V>::freeList() {
    Node<K, V> *p = header;
    Node<K, V> *q;
    while (p != nullptr) {
        q = p->forward[0];
        memoryPool.deallocate(p);
        p = q;
    }
}

// 查找指定键的节点
template<typename K, typename V>
Node<K, V> *SkipList<K, V>::search(const K key) const {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V> *node = header;
    for (int i = level; i >= 0; --i) {
        while ((node->forward[i])->key < key) {
            node = *(node->forward + i);
        }
    }
    node = node->forward[0];
    if (node->key == key) {
        return node;
    } else {
        return nullptr;
    }
}

// 插入键值对
template<typename K, typename V>
bool SkipList<K, V>::insert(K key, V value) {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V> *update[MAX_LEVEL];
    Node<K, V> *node = header;
    for (int i = level; i >= 0; --i) {
        while ((node->forward[i])->key < key) {
            node = node->forward[i];
        }
        update[i] = node;
    }
    node = node->forward[0];
    if (node->key == key) {
        return false;
    }
    int nodeLevel = getRandomLevel();
    if (nodeLevel > level) {
        nodeLevel = ++level;
        update[nodeLevel] = header;
    }
    Node<K, V> *newNode;
    createNode(nodeLevel, newNode, key, value);
    for (int i = nodeLevel; i >= 0; --i) {
        node = update[i];
        newNode->forward[i] = node->forward[i];
        node->forward[i] = newNode;
    }
    ++nodeCount;
    return true;
}

// 删除指定键的节点，并返回其值
template<typename K, typename V>
bool SkipList<K, V>::remove(K key, V &value) {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V> *update[MAX_LEVEL];
    Node<K, V> *node = header;
    for (int i = level; i >= 0; --i) {
        while ((node->forward[i])->key < key) {
            node = node->forward[i];
        }
        update[i] = node;
    }
    node = node->forward[0];
    if (node->key != key) {
        return false;
    }
    value = node->value;
    for (int i = 0; i <= level; ++i) {
        if (update[i]->forward[i] != node) {
            break;
        }
        update[i]->forward[i] = node->forward[i];
    }
    memoryPool.deallocate(node);
    while (level > 0 && header->forward[level] == footer) {
        --level;
    }
    --nodeCount;
    return true;
}

// 获取随机层级
template<typename K, typename V>
int SkipList<K, V>::getRandomLevel() {
    int level = rand() % MAX_LEVEL;
    if (level == 0) {
        level = 1;
    }
    return level;
}

#endif //SKIPLISTPRO_SKIPLIST_H
