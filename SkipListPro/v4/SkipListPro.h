#ifndef SKIPLIST_PRO_H
#define SKIPLIST_PRO_H

#include "Node.h"
#include "MemoryPool.h"
#include <vector>
#include <mutex>
#include <ctime>
#include <cmath>
#include <cassert>

template<typename K, typename V>
class SkipListPro {
public:
    explicit SkipListPro(int maxLevel = 18);
    ~SkipListPro();
    
    bool insert(K key, V value);
    bool remove(K key);
    V search(K key);
    int size() const { return nodeCount_; }

private:
    int randomLevel();
    void rebalance();
    void validateForwardPointers(); // 新增校验方法

    int maxLevel_;
    int currentLevel_;
    Node<K, V>* header_;
    Node<K, V>* tail_;
    size_t nodeCount_;
    MemoryPool<Node<K, V>> memoryPool_;
    mutable std::mutex mtx_;
};

template<typename K, typename V>
SkipListPro<K, V>::SkipListPro(int maxLevel) : 
    maxLevel_(maxLevel > 0 ? maxLevel : 1),
    currentLevel_(0),
    nodeCount_(0),
    memoryPool_(1024) {
    header_ = memoryPool_.allocate(K(), V(), maxLevel_);
    tail_ = memoryPool_.allocate(K(), V(), 0);
    for (int i = 0; i <= maxLevel_; ++i) {
        header_->forward[i] = tail_;
    }
}

template<typename K, typename V>
SkipListPro<K, V>::~SkipListPro() {
    Node<K, V>* current = header_->forward[0];
    while (current != tail_) {
        Node<K, V>* next = current->forward[0];
        memoryPool_.deallocate(current);
        current = next;
    }
    memoryPool_.deallocate(header_);
    memoryPool_.deallocate(tail_);
}

template<typename K, typename V>
int SkipListPro<K, V>::randomLevel() {
    static thread_local unsigned seed = time(nullptr);
    int level = 1;
    double probability = 1.0 / (1 + log2(nodeCount_ + 2));
    while ((rand_r(&seed) % 100) < (probability * 100) && level < maxLevel_) {
        level++;
    }
    return level;
}

template<typename K, typename V>
bool SkipListPro<K, V>::insert(K key, V value) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::vector<Node<K, V>*> update(maxLevel_ + 1, nullptr);
    Node<K, V>* current = header_;

    for (int i = currentLevel_; i >= 0; --i) {
        while (current->forward[i] != tail_ && 
               current->forward[i]->getKey() < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current != tail_ && current->getKey() == key) {
        return false;
    }

    int level = randomLevel();
    if (level > currentLevel_) {
        for (int i = currentLevel_ + 1; i <= level; ++i) {
            update[i] = header_;
        }
        currentLevel_ = level;
    }

    Node<K, V>* newNode = memoryPool_.allocate(key, value, level);
    for (int i = 0; i <= level; ++i) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }

    nodeCount_++;
    rebalance();
    return true;
}

template<typename K, typename V>
bool SkipListPro<K, V>::remove(K key) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::vector<Node<K, V>*> update(maxLevel_ + 1, nullptr);
    Node<K, V>* current = header_;

    // 修复1：遍历所有层级查找前驱节点
    for (int i = currentLevel_; i >= 0; --i) {
        while (current->forward[i] != tail_ && 
               current->forward[i]->getKey() < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current == tail_ || current->getKey() != key) {
        return false;
    }

    // 修复2：正确更新所有相关层级指针
    for (int i = 0; i <= current->nodeLevel; ++i) {  // 改为使用节点的实际层级
        if (update[i]->forward[i] != current) break;
        update[i]->forward[i] = current->forward[i];
    }

    memoryPool_.deallocate(current);
    nodeCount_--;

    // 修复3：层级校验加强
    while (currentLevel_ > 0 && header_->forward[currentLevel_] == tail_) {
        currentLevel_--;
    }

    rebalance();
    validateForwardPointers(); // 新增校验
    return true;
}

template<typename K, typename V>
V SkipListPro<K, V>::search(K key) {
    std::lock_guard<std::mutex> lock(mtx_);
    Node<K, V>* current = header_;
    for (int i = currentLevel_; i >= 0; --i) {
        while (current->forward[i] != tail_ && 
               current->forward[i]->getKey() < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    return (current != tail_ && current->getKey() == key) ? 
           current->getValue() : V();
}

template<typename K, typename V>
void SkipListPro<K, V>::rebalance() {
    int expectedLevel = ceil(log2(nodeCount_ + 1));
    expectedLevel = std::min(expectedLevel, maxLevel_);
    currentLevel_ = std::min(currentLevel_, expectedLevel);
}

// 新增方法：校验指针有效性
template<typename K, typename V>
void SkipListPro<K, V>::validateForwardPointers() {
    for (int i = 0; i <= currentLevel_; ++i) {
        Node<K, V>* node = header_->forward[i];
        while (node != tail_) {
            assert(node != nullptr);
            assert(node->forward[i] != nullptr);
            node = node->forward[i];
        }
    }
}

#endif // SKIPLIST_PRO_H
