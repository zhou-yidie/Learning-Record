#ifndef SKIPLISTPRO_MEMORYPOOL_H
#define SKIPLISTPRO_MEMORYPOOL_H

#include <vector>

template<typename T>
class MemoryPool {
public:
    MemoryPool(size_t size) {
        for (size_t i = 0; i < size; ++i) {
            pool_.push_back(new T());
        }
    }

    ~MemoryPool() {
        for (auto ptr : pool_) {
            delete ptr;
        }
    }

    T* allocate() {
        if (pool_.empty()) {
            return new T();
        }
        T* ptr = pool_.back();
        pool_.pop_back();
        return ptr;
    }

    void deallocate(T* ptr) {
        pool_.push_back(ptr);
    }

private:
    std::vector<T*> pool_;
};

#endif //SKIPLISTPRO_MEMORYPOOL_H
