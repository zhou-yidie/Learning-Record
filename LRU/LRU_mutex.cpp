#include <iostream>
#include <list>
#include <unordered_map>
#include <shared_mutex>

template<typename K, typename V>
class ThreadSafeLRUCache {
private:
    // 缓存容量
    size_t capacity;
    // 存储键值对的链表，链表头部表示最近使用的元素
    std::list<std::pair<K, V>> cacheList;
    // 哈希表，用于快速查找键对应的链表迭代器
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cacheMap;
    // 读写锁
    mutable std::shared_mutex rwMutex;

public:
    // 构造函数，初始化缓存容量
    ThreadSafeLRUCache(size_t cap) : capacity(cap) {}

    // 获取缓存中的值
    V get(const K& key) {
        std::shared_lock<std::shared_mutex> readLock(rwMutex);
        auto it = cacheMap.find(key);
        if (it == cacheMap.end()) {
            return V(); // 如果键不存在，返回默认值
        }
        // 将该元素移动到链表头部，表示最近使用
        std::pair<K, V> kv = *it->second;
        cacheList.erase(it->second);
        cacheList.push_front(kv);
        cacheMap[key] = cacheList.begin();
        return kv.second;
    }

    // 插入或更新缓存中的值
    void put(const K& key, const V& value) {
        std::unique_lock<std::shared_mutex> writeLock(rwMutex);
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            // 如果键已存在，更新值并将该元素移动到链表头部
            cacheList.erase(it->second);
        } else if (cacheList.size() == capacity) {
            // 如果缓存已满，删除链表尾部元素（最久未使用的元素）
            K lastKey = cacheList.back().first;
            cacheMap.erase(lastKey);
            cacheList.pop_back();
        }
        // 插入新元素到链表头部
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
};

#include <thread>
#include <vector>

void testThreadSafeLRU() {
    ThreadSafeLRUCache<int, int> cache(3);

    auto writer = [&cache]() {
        for (int i = 0; i < 5; ++i) {
            cache.put(i, i * 10);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    auto reader = [&cache]() {
        for (int i = 0; i < 5; ++i) {
            int value = cache.get(i);
            std::cout << "Read key " << i << ", value: " << value << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    };

    std::vector<std::thread> threads;
    threads.emplace_back(writer);
    threads.emplace_back(reader);

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    testThreadSafeLRU();
    return 0;
}