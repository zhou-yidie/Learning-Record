#ifndef SKIPLISTPRO_SKIPLIST_H
#define SKIPLISTPRO_SKIPLIST_H

#include <cstddef>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include "Node.h"

#define MAX_LEVEL 16

template<typename K, typename V>
class SkipListPro {
public:
    SkipListPro(K footerKey) : level(0), nodeCount(0) {
        createList(footerKey);
    }

    ~SkipListPro() { freeList(); }

    Node<K, V>* search(K key) const;
    bool insert(K key, V value);
    bool remove(K key, V& value);

    int size() const { return nodeCount; }
    int getLevel() const { return level; }

private:
    void createList(K footerKey);
    void freeList();
    void createNode(int level, Node<K, V>*& node);
    void createNode(int level, Node<K, V>*& node, K key, V value);
    int getRandomLevel() {
        static unsigned int seed = static_cast<unsigned int>(time(nullptr));
        return rand_r(&seed) % MAX_LEVEL + 1;  // 修正函数调用
    };

    int level;
    Node<K, V>* header;
    Node<K, V>* footer;
    size_t nodeCount;
    mutable std::mutex mtx;
};

// template<typename K, typename V>
// int SkipList<K, V>::getRandomLevel() {
//     static unsigned seed = time(nullptr);
//     return rand_r(&seed) % MAX_LEVEL + 1;
// }

template<typename K, typename V>
void SkipListPro<K, V>::createList(K footerKey) {
    createNode(0, footer);
    footer->key = footerKey;
    createNode(MAX_LEVEL, header);
    for (int i = 0; i <= MAX_LEVEL; ++i) {
        header->forward[i] = footer;
    }
}

template<typename K, typename V>
void SkipListPro<K, V>::createNode(int level, Node<K, V>*& node) {
    node = new Node<K, V>();
    node->forward = new Node<K, V>*[level + 1]();
    node->nodeLevel = level;
}

template<typename K, typename V>
void SkipListPro<K, V>::createNode(int level, Node<K, V>*& node, K key, V value) {
    node = new Node<K, V>(key, value, level);
}

template<typename K, typename V>
void SkipListPro<K, V>::freeList() {
    Node<K, V>* p = header;
    while (p != footer) {
        Node<K, V>* next = p->forward[0];
        delete p;
        p = next;
    }
    delete footer;
    header = footer = nullptr;
}

template<typename K, typename V>
Node<K, V>* SkipListPro<K, V>::search(K key) const {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V>* node = header;
    for (int i = level; i >= 0; --i) {
        while (node->forward[i]->key < key) 
            node = node->forward[i];
    }
    node = node->forward[0];
    return (node->key == key) ? node : nullptr;
}

template<typename K, typename V>
bool SkipListPro<K, V>::insert(K key, V value) {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V>* update[MAX_LEVEL + 1];
    Node<K, V>* node = header;
    
    for (int i = level; i >= 0; --i) {
        while (node->forward[i]->key < key)
            node = node->forward[i];
        update[i] = node;
    }
    node = node->forward[0];
    
    if (node->key == key) return false;
    
    int newLevel = getRandomLevel();
    if (newLevel > level) {
        for (int i = level + 1; i <= newLevel; ++i)
            update[i] = header;
        level = newLevel;
    }
    
    Node<K, V>* newNode;
    createNode(newLevel, newNode, key, value);
    for (int i = 0; i <= newLevel; ++i) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    ++nodeCount;
    return true;
}

template<typename K, typename V>
bool SkipListPro<K, V>::remove(K key, V& value) {
    std::lock_guard<std::mutex> lock(mtx);
    Node<K, V>* update[MAX_LEVEL + 1];
    Node<K, V>* node = header;
    
    for (int i = level; i >= 0; --i) {
        while (node->forward[i]->key < key)
            node = node->forward[i];
        update[i] = node;
    }
    node = node->forward[0];
    
    if (node->key != key) return false;
    value = node->value;
    
    for (int i = 0; i <= level; ++i) {
        if (update[i]->forward[i] != node) break;
        update[i]->forward[i] = node->forward[i];
    }
    delete node;
    
    while (level > 0 && header->forward[level] == footer)
        --level;
    --nodeCount;
    return true;
}


#endif // SKIPLISTPRO_SKIPLIST_H
