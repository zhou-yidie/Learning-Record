#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <vector>
#include <mutex>

// 内存池
template<typename T>
class MemoryPool {
public:
    // 构造函数
    explicit MemoryPool(size_t chunkSize = 1024) : chunkSize_(chunkSize) {}

    // 分配对象
    template<typename... Args>
    T* allocate(Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (pool_.empty()) {
            expandPool();
        }
        T* obj = pool_.back();
        pool_.pop_back();
        new (obj) T(std::forward<Args>(args)...);
        return obj;
    }

    // 回收对象
    void deallocate(T* obj) {
        std::lock_guard<std::mutex> lock(mtx_);
        obj->~T();
        pool_.push_back(obj);
    }

private:
    // 扩展内存池
    void expandPool() {
        for (size_t i = 0; i < chunkSize_; ++i) {
            pool_.push_back(static_cast<T*>(::operator new(sizeof(T))));
        }
    }

    // 内存池
    std::vector<T*> pool_;
    // 每次扩展的大小
    size_t chunkSize_;
    // 互斥锁
    std::mutex mtx_;
};

#endif // MEMORY_POOL_H
