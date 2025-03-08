#ifndef SKIPLISTPRO_MEMORYPOOL_H
#define SKIPLISTPRO_MEMORYPOOL_H

#include <vector>

template<typename T>
class MemoryPool {
public:
    MemoryPool(size_t size) {}
    ~MemoryPool() {}
    
    T* allocate() { return new T(); }
    void deallocate(T* ptr) { delete ptr; }
};

#endif // SKIPLISTPRO_MEMORYPOOL_H
