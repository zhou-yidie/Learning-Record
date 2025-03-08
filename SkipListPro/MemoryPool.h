// MemoryPool.h
#ifndef SKIPLISTPRO_MEMORYPOOL_H
#define SKIPLISTPRO_MEMORYPOOL_H

#include <vector>

// 内存池类，用于管理节点的内存分配和释放
template<typename T>
class MemoryPool {
public:
    // 构造函数，初始化内存池，预分配一定数量的节点
    MemoryPool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            pool_.push_back(new T());
        }
    }

    // 析构函数，释放内存池中所有节点的内存
    ~MemoryPool() {
        for (auto ptr : pool_) {
            delete ptr;
        }
    }

    // 从内存池中分配一个节点
    T* allocate() {
        if (pool_.empty()) {
            return new T();
        }
        T* ptr = pool_.back();
        pool_.pop_back();
        return ptr;
    }

    // 将一个节点释放回内存池
    void deallocate(T* ptr) {
        pool_.push_back(ptr);
    }

private:
    std::vector<T*> pool_;  // 存储空闲节点的向量
};

#endif //SKIPLISTPRO_MEMORYPOOL_H
