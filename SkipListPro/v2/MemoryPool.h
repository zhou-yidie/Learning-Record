#ifndef SKIPLIST_PRO_H
#define SKIPLIST_PRO_H

#include "Node.h"
#include "MemoryPool.h"
#include <vector>
#include <atomic>
#include <random>
#include <cmath>
#include <mutex>
#include <limits>

// 跳表类，实现了自平衡、内存优化和并发性能优化
template<typename K, typename V>
class SkipListPro {
public:
    // 构造函数，初始化跳表的最大层级
    explicit SkipListPro(int maxLevel = 18) : 
        maxLevel_(maxLevel), currentLevel_(0), nodeCount_(0), 
        memoryPool_(1024), rebalanceThreshold_(1000) {
        // 分配头节点和尾节点的内存
        header_ = memoryPool_.allocate(std::numeric_limits<K>::min(), V(), maxLevel_);
        tail_ = memoryPool_.allocate(std::numeric_limits<K>::max(), V(), 0);
        // 初始化头节点的 forward 数组，使其指向尾节点
        for (int i = 0; i <= maxLevel_; ++i) {
            header_->forward[i].store(tail_, std::memory_order_relaxed);
        }
    }

    // 析构函数，释放跳表的所有节点内存
    ~SkipListPro() {
        Node<K, V>* current = header_->forward[0].load(std::memory_order_relaxed);
        while (current != tail_) {
            Node<K, V>* next = current->forward[0].load(std::memory_order_relaxed);
            memoryPool_.deallocate(current);
            current = next;
        }
        memoryPool_.deallocate(header_);
        memoryPool_.deallocate(tail_);
    }

    // 插入一个键值对到跳表中
    bool insert(K key, V value) {
        std::vector<Node<K, V>*> update(maxLevel_ + 1, nullptr);
        Node<K, V>* current = header_;

        // 查找插入位置
        for (int i = currentLevel_; i >= 0; --i) {
            while (current->forward[i].load(std::memory_order_relaxed) != tail_ &&
                   current->forward[i].load(std::memory_order_relaxed)->getKey() < key) {
                current = current->forward[i].load(std::memory_order_relaxed);
            }
            update[i] = current;
        }

        current = current->forward[0].load(std::memory_order_relaxed);
        if (current != tail_ && current->getKey() == key) {
            return false;  // 键已存在，插入失败
        }

        int level = randomLevel();  // 随机生成节点的层级
        if (level > currentLevel_) {
            for (int i = currentLevel_ + 1; i <= level; ++i) {
                update[i] = header_;
            }
            currentLevel_ = level;
        }

        Node<K, V>* newNode = memoryPool_.allocate(key, value, level);  // 分配新节点的内存

        // 使用 CAS 操作插入新节点
        for (int i = 0; i <= level; ++i) {
            newNode->forward[i].store(update[i]->forward[i].load(std::memory_order_relaxed), std::memory_order_relaxed);
            while (!update[i]->forward[i].compare_exchange_weak(
                newNode->forward[i].load(std::memory_order_relaxed), 
                newNode, 
                std::memory_order_release, 
                std::memory_order_relaxed
            ));
        }

        ++nodeCount_;

        // 检查是否需要进行再平衡
        if (nodeCount_ % rebalanceThreshold_ == 0) {
            rebalance();
        }

        return true;
    }

    // 从跳表中删除指定键的节点
    bool remove(K key) {
        std::vector<Node<K, V>*> update(maxLevel_ + 1, nullptr);
        Node<K, V>* current = header_;

        // 查找要删除的节点
        for (int i = currentLevel_; i >= 0; --i) {
            while (current->forward[i].load(std::memory_order_relaxed) != tail_ &&
                   current->forward[i].load(std::memory_order_relaxed)->getKey() < key) {
                current = current->forward[i].load(std::memory_order_relaxed);
            }
            update[i] = current;
        }

        current = current->forward[0].load(std::memory_order_relaxed);
        if (current == tail_ || current->getKey() != key) {
            return false;  // 键不存在，删除失败
        }

        // 使用 CAS 操作删除节点
        for (int i = 0; i <= current->nodeLevel; ++i) {
            while (!update[i]->forward[i].compare_exchange_weak(
                current, 
                current->forward[i].load(std::memory_order_relaxed), 
                std::memory_order_release, 
                std::memory_order_relaxed
            ));
        }

        memoryPool_.deallocate(current);  // 释放节点内存
        --nodeCount_;

        // 更新当前层级
        while (currentLevel_ > 0 && header_->forward[currentLevel_].load(std::memory_order_relaxed) == tail_) {
            --currentLevel_;
        }

        return true;
    }

    // 在跳表中查找指定键的值
    V search(K key) {
        Node<K, V>* current = header_;
        for (int i = currentLevel_; i >= 0; --i) {
            while (current->forward[i].load(std::memory_order_relaxed) != tail_ &&
                   current->forward[i].load(std::memory_order_relaxed)->getKey() < key) {
                current = current->forward[i].load(std::memory_order_relaxed);
            }
        }
        current = current->forward[0].load(std::memory_order_relaxed);
        return (current != tail_ && current->getKey() == key) ? current->getValue() : V();
    }

    // 获取跳表中节点的数量
    int size() const {
        return nodeCount_;
    }

private:
    // 随机生成节点的层级
    int randomLevel() {
        static thread_local std::mt19937 generator(std::random_device{}());
        static thread_local std::uniform_real_distribution<> distribution(0.0, 1.0);
        int level = 1;
        double probability = 1.0 / (1 + log2(nodeCount_ + 2));
        while (distribution(generator) < probability && level < maxLevel_) {
            ++level;
        }
        return level;
    }

    // 再平衡跳表，重新生成索引层
    void rebalance() {
        // 简单的再平衡策略：重新构建跳表
        std::vector<std::pair<K, V>> data;
        Node<K, V>* current = header_->forward[0].load(std::memory_order_relaxed);
        while (current != tail_) {
            data.emplace_back(current->getKey(), current->getValue());
            current = current->forward[0].load(std::memory_order_relaxed);
        }

        // 清空当前跳表
        current = header_->forward[0].load(std::memory_order_relaxed);
        while (current != tail_) {
            Node<K, V>* next = current->forward[0].load(std::memory_order_relaxed);
            memoryPool_.deallocate(current);
            current = next;
        }
        currentLevel_ = 0;
        nodeCount_ = 0;

        // 重新插入数据
        for (const auto& pair : data) {
            insert(pair.first, pair.second);
        }
    }

    int maxLevel_;  // 跳表的最大层级
    int currentLevel_;  // 跳表的当前层级
    Node<K, V>* header_;  // 头节点
    Node<K, V>* tail_;  // 尾节点
    std::atomic<int> nodeCount_;  // 跳表中节点的数量
    MemoryPool<Node<K, V>> memoryPool_;  // 内存池，用于节点的内存管理
    int rebalanceThreshold_;  // 再平衡的阈值，当节点数量达到该阈值时进行再平衡
};

#endif // SKIPLIST_PRO_H
