#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <vector>
#include <mutex>

template<typename T>
class MemoryPool {
public:
    explicit MemoryPool(size_t chunkSize = 1024) : chunkSize_(chunkSize) {}
    
    template<typename... Args>
    T* allocate(Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (pool_.empty()) expandPool();
        T* obj = pool_.back();
        pool_.pop_back();
        new (obj) T(std::forward<Args>(args)...);
        return obj;
    }

    void deallocate(T* obj) {
        std::lock_guard<std::mutex> lock(mtx_);
        obj->~T();
        pool_.push_back(obj);
    }

private:
    void expandPool() {
        for (size_t i = 0; i < chunkSize_; ++i) {
            pool_.push_back(static_cast<T*>(::operator new(sizeof(T))));
        }
    }

    std::vector<T*> pool_;
    size_t chunkSize_;
    std::mutex mtx_;
};

#endif // MEMORY_POOL_H
