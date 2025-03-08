#ifndef SKIPLISTPRO_SKIPLIST_H
#define SKIPLISTPRO_SKIPLIST_H

#include <cstddef>
#include <cassert>
#include <ctime>
#include <mutex>
#include "Node.h"
#include "MemoryPool.h"

template<typename K, typename V>
class SkipList {
public:
    SkipList(K footerKey) : rnd(0x12345678), memoryPool(100) {
        createList(footerKey);
    }

    ~SkipList() {
        freeList();
    }

    Node<K, V> *search(K key) const;
    bool insert(K key, V value);
    bool remove(K key, V &value);

    int size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return nodeCount;
    }

    int getLevel() const {
        std::lock_guard<std::mutex> lock(mtx);
        return level;
    }

private:
    void createList(K footerKey);
    void freeList();
    void createNode(int level, Node<K, V> *&node);
    void createNode(int level, Node<K, V> *&node, K key, V value);
    int getRandomLevel();

    int level;
    Node<K, V> *header;
    Node<K, V> *footer;
    size_t nodeCount;
    static const int MAX_LEVEL = 16;
    MemoryPool<Node<K, V>> memoryPool;
    mutable std::mutex mtx;
    unsigned int rnd;
};

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

template<typename K, typename V>
void SkipList<K, V>::createNode(int level, Node<K, V> *&node) {
    node = memoryPool.allocate();
    node->forward = new Node<K, V>*[level + 1];
    node->nodeLevel = level;
    assert(node != nullptr);
}

template<typename K, typename V>
void SkipList<K, V>::createNode(int level, Node<K, V> *&node, K key, V value) {
    node = memoryPool.allocate();
    node->key = key;
    node->value = value;
    node->forward = new Node<K, V>*[level + 1];
    node->nodeLevel = level;
    assert(node != nullptr);
}

template<typename K, typename V>
void SkipList<K, V>::freeList() {
    Node<K, V> *p = header;
    Node<K, V> *q;
    while (p != nullptr) {
        q = p->forward[0];
        delete[] p->forward;
        p->forward = nullptr;
        memoryPool.deallocate(p);
        p = q;
    }
}

template<typename K, typename V>
Node<K, V> *SkipList<K, V>::search(const K key) const {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V> *node = header;
    for (int i = level; i >= 0; --i) {
        while (node->forward[i]->key < key) {
            node = node->forward[i];
        }
    }
    node = node->forward[0];
    return (node->key == key) ? node : nullptr;
}

template<typename K, typename V>
bool SkipList<K, V>::insert(K key, V value) {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V> *update[MAX_LEVEL + 1];
    Node<K, V> *node = header;
    for (int i = level; i >= 0; --i) {
        while (node->forward[i]->key < key) {
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
        for (int i = level + 1; i <= nodeLevel; ++i) {
            update[i] = header;
        }
        level = nodeLevel;
    }
    Node<K, V> *newNode;
    createNode(nodeLevel, newNode, key, value);
    for (int i = 0; i <= nodeLevel; ++i) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    ++nodeCount;
    return true;
}

template<typename K, typename V>
bool SkipList<K, V>::remove(K key, V &value) {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V> *update[MAX_LEVEL + 1];
    Node<K, V> *node = header;
    for (int i = level; i >= 0; --i) {
        while (node->forward[i]->key < key) {
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
        if (update[i]->forward[i] != node) break;
        update[i]->forward[i] = node->forward[i];
    }
    delete[] node->forward;
    node->forward = nullptr;
    memoryPool.deallocate(node);
    while (level > 0 && header->forward[level] == footer) {
        --level;
    }
    --nodeCount;
    return true;
}

template<typename K, typename V>
int SkipList<K, V>::getRandomLevel() {
    rnd = rnd * 1103515245 + 12345;
    int level = rnd % MAX_LEVEL;
    level = std::min(level, 98);
    return level > 0 ? level : 1;
}

#endif //SKIPLISTPRO_SKIPLIST_H
