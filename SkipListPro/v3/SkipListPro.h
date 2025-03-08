#ifndef SKIPLIST_PRO_H
#define SKIPLIST_PRO_H

#include "Node.h"
#include "MemoryPool.h"
#include <vector>
#include <mutex>
#include <cmath>
#include <cassert>
#include <atomic>

// 跳表
template<typename K, typename V>
class SkipListPro {
public:
    // 构造函数
    explicit SkipListPro(int maxLevel = 18) : 
        maxLevel_(maxLevel > 0 ? maxLevel : 1),
        currentLevel_(0),
        nodeCount_(0),
        memoryPool_(1024) {
        // 初始化头节点和尾节点
        header_ = memoryPool_.allocate(K(), V(), maxLevel_);
        tail_ = memoryPool_.allocate(K(), V(), 0);
        for (int i = 0; i <= maxLevel_; ++i) {
            header_->forward[i].store(tail_);
        }
    }

    // 析构函数
    ~SkipListPro() {
        // 回收所有节点
        Node<K, V>* current = header_->forward[0].load();
        while (current != tail_) {
            Node<K, V>* next = current->forward[0].load();
            memoryPool_.deallocate(current);
            current = next;
        }
        memoryPool_.deallocate(header_);
        memoryPool_.deallocate(tail_);
    }

    // 插入操作
    bool insert(K key, V value) {
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<Node<K, V>*> update(maxLevel_ + 1, nullptr);
        Node<K, V>* current = header_;

        // 查找插入位置
        for (int i = currentLevel_; i >= 0; --i) {
            while (current->forward[i].load() != tail_ && 
                   current->forward[i].load()->getKey() < key) {
                current = current->forward[i].load();
            }
            update[i] = current;
        }

        current = current->forward[0].load();
        if (current != tail_ && current->getKey() == key) {
            return false;
        }

        // 计算随机层级
        int level = randomLevel();
        if (level > currentLevel_) {
            for (int i = currentLevel_ + 1; i <= level; ++i) {
                update[i] = header_;
            }
            currentLevel_ = level;
        }

        // 创建新节点
        Node<K, V>* newNode = memoryPool_.allocate(key, value, level);
        for (int i = 0; i <= level; ++i) {
            newNode->forward[i].store(update[i]->forward[i].load());
            update[i]->forward[i].store(newNode);
        }

        nodeCount_++;
        rebalance();
        return true;
    }

    // 删除操作
    bool remove(K key) {
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<Node<K, V>*> update(maxLevel_ + 1, nullptr);
        Node<K, V>* current = header_;

        // 查找删除位置
        for (int i = currentLevel_; i >= 0; --i) {
            while (current->forward[i].load() != tail_ && 
                   current->forward[i].load()->getKey() < key) {
                current = current->forward[i].load();
            }
            update[i] = current;
        }

        current = current->forward[0].load();
        if (current == tail_ || current->getKey() != key) {
            return false;
        }

        // 更新指针
        for (int i = 0; i <= current->nodeLevel; ++i) {
            if (update[i]->forward[i].load() != current) break;
            update[i]->forward[i].store(current->forward[i].load());
        }

        memoryPool_.deallocate(current);
        nodeCount_--;

        // 调整当前层级
        while (currentLevel_ > 0 && header_->forward[currentLevel_].load() == tail_) {
            currentLevel_--;
        }

        rebalance();
        return true;
    }

    // 查找操作
    V search(K key) const {
        std::lock_guard<std::mutex> lock(mtx_);
        Node<K, V>* current = header_;
        for (int i = currentLevel_; i >= 0; --i) {
            while (current->forward[i].load() != tail_ && 
                   current->forward[i].load()->getKey() < key) {
                current = current->forward[i].load();
            }
        }
        current = current->forward[0].load();
        return (current != tail_ && current->getKey() == key) ? 
               current->getValue() : V();
    }

    // 获取元素个数
    int size() const {
        return nodeCount_;
    }

private:
    // 随机生成层级
    int randomLevel() {
        std::uniform_int_distribution<int> dist(0, 99);
        int level = 1;
        double probability = 1.0 / (1 + std::log2(nodeCount_ + 2));
        while (dist(generator_) < (probability * 100) && level < maxLevel_) {
            level++;
        }
        return level;
    }

    // 重新平衡跳表
    void rebalance() {
        int expectedLevel = static_cast<int>(std::ceil(std::log2(nodeCount_ + 1)));
        expectedLevel = std::min(expectedLevel, maxLevel_);
        currentLevel_ = std::min(currentLevel_, expectedLevel);
    }

    // 最大层级
    int maxLevel_;
    // 当前层级
    int currentLevel_;
    // 头节点
    Node<K, V>* header_;
    // 尾节点
    Node<K, V>* tail_;
    // 元素个数
    size_t nodeCount_;
    // 内存池
    MemoryPool<Node<K, V>> memoryPool_;
    // 互斥锁
    mutable std::mutex mtx_;
    std::mt19937 generator_;
    std::random_device seed_;
};

#endif // SKIPLIST_PRO_H
