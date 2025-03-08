#ifndef SKIPLIST_PRO_H
#define SKIPLIST_PRO_H

#include <iostream>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <memory>

// 前置声明
template<typename K, typename V>
class SkipListPro;

// 跳表节点类（无需默认构造函数）
template<typename K, typename V>
class Node {
    friend class SkipListPro<K, V>;
public:
    Node(K k, V v, int level) : 
        key(k), value(v), nodeLevel(level) {
        forward = new Node<K, V>*[level + 1]();
    }
    
    ~Node() {
        delete[] forward;
    }

    K getKey() const { return key; }
    V getValue() const { return value; }

    Node<K, V>** forward;
    int nodeLevel;

private:
    K key;
    V value;
};

// 改进的内存池类（支持构造参数）
template<typename T>
class MemoryPool {
public:
    MemoryPool(size_t chunkSize = 1024) : chunkSize_(chunkSize) {}
    
    ~MemoryPool() {
        clear();
    }

    template<typename... Args>
    T* allocate(Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (pool_.empty()) {
            expandPool();
        }
        T* obj = pool_.back();
        pool_.pop_back();
        new (obj) T(std::forward<Args>(args)...); // Placement new
        return obj;
    }

    void deallocate(T* obj) {
        std::lock_guard<std::mutex> lock(mtx_);
        obj->~T();
        pool_.push_back(obj);
    }

private:
    void expandPool() {
        try {
            for (size_t i = 0; i < chunkSize_; ++i) {
                // 预分配内存但不构造对象
                pool_.push_back(static_cast<T*>(::operator new(sizeof(T))));
            }
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        }
    }

    void clear() {
        for (auto ptr : pool_) {
            ::operator delete(ptr);
        }
        pool_.clear();
    }

    std::vector<T*> pool_;
    size_t chunkSize_;
    std::mutex mtx_;
};

// 增强版跳表类
template<typename K, typename V>
class SkipListPro {
public:
    explicit SkipListPro(int maxLevel = 18) : 
        maxLevel_(maxLevel), 
        currentLevel_(0), 
        nodeCount_(0),
        memoryPool_(1024) {
        // 使用内存池创建哨兵节点
        header_ = memoryPool_.allocate(K(), V(), maxLevel_);
        tail_ = memoryPool_.allocate(K(), V(), 0);
        for (int i = 0; i <= maxLevel_; ++i) {
            header_->forward[i] = tail_;
        }
    }
    
    ~SkipListPro() {
        Node<K, V>* current = header_->forward[0];
        while (current != tail_) {
            Node<K, V>* next = current->forward[0];
            memoryPool_.deallocate(current);
            current = next;
        }
        memoryPool_.deallocate(header_);
        memoryPool_.deallocate(tail_);
    }

    bool insert(K key, V value) {
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
                if (i < update.size()) {  // 检查边界
                    update[i] = header_;
                }
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

    bool remove(K key) {
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
        if (current == tail_ || current->getKey() != key) {
            return false;
        }

        for (int i = 0; i <= currentLevel_ && update[i] != nullptr; ++i) {  // 检查边界
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }

        memoryPool_.deallocate(current);
        nodeCount_--;

        while (currentLevel_ > 0 && header_->forward[currentLevel_] == tail_) {
            currentLevel_--;
        }

        rebalance();
        return true;
    }

    V search(K key) {
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

    int size() const { return nodeCount_; }

private:
    int randomLevel() {
        static thread_local unsigned seed = time(nullptr);
        int level = 1;
        double probability = 1.0 / (1 + log2(nodeCount_ + 1));
        while ((rand_r(&seed) % 100) < (probability * 100) && level < maxLevel_) {
            level++;
        }
        return level;
    }

    void rebalance() {
        int expectedLevel = ceil(log2(nodeCount_ + 1));
        expectedLevel = std::min(expectedLevel, maxLevel_);
        currentLevel_ = std::min(currentLevel_, expectedLevel);
    }

    int maxLevel_;
    int currentLevel_;
    Node<K, V>* header_;
    Node<K, V>* tail_;
    size_t nodeCount_;
    MemoryPool<Node<K, V>> memoryPool_;
    mutable std::mutex mtx_;
};

#endif // SKIPLIST_PRO_H
