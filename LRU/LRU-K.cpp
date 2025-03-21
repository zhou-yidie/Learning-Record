#include <unordered_map>
#include <deque>
#include <set>
#include <ctime>

using namespace std;

// 历史记录条目结构：记录未被提升到缓存的页面的访问信息
struct HistoryEntry {
    int access_count;          // 访问次数
    deque<time_t> access_times; // 访问时间戳队列
};

// 缓存条目结构：记录已提升到缓存的页面的访问信息
struct CacheEntry {
    deque<time_t> access_times; // 最近K次访问时间戳队列
    time_t kth_access_time;     // 第K次访问时间（用于淘汰判断）
};

class LRUKCache {
private:
    int k;              // K次访问后进入缓存
    size_t capacity;    // 缓存容量
    time_t current_time;// 模拟时间戳
    
    // 数据结构说明：
    unordered_map<int, HistoryEntry> history_map;  // 历史记录表（哈希表实现O(1)查找）
    unordered_map<int, CacheEntry> cache_map;       // 缓存表（哈希表实现O(1)查找）
    set<pair<time_t, int>> cache_tree;             // 按第K次访问时间排序（红黑树实现有序性）

public:
    LRUKCache(int k, size_t capacity) : k(k), capacity(capacity), current_time(0) {}

    // 访问键值对的主函数
    void access(int key) {
        current_time++; // 每次访问时间戳递增

        // 情况1：键存在于缓存中
        auto cache_it = cache_map.find(key);
        if (cache_it != cache_map.end()) {
            // 更新缓存条目信息
            CacheEntry& entry = cache_it->second;
            entry.access_times.push_back(current_time);
            
            // 维护队列大小不超过K
            if (entry.access_times.size() > k) {
                entry.access_times.pop_front();
            }
            
            // 更新排序依据（第K次访问时间）
            time_t old_time = entry.kth_access_time;
            entry.kth_access_time = entry.access_times.front();
            
            // 更新红黑树中的排序位置
            cache_tree.erase({old_time, key});
            cache_tree.insert({entry.kth_access_time, key});
            return;
        }

        // 情况2：键存在于历史记录
        auto hist_it = history_map.find(key);
        if (hist_it != history_map.end()) {
            HistoryEntry& entry = hist_it->second;
            entry.access_count++;
            entry.access_times.push_back(current_time);

            // 达到K次访问，提升到缓存
            if (entry.access_count >= k) {
                // 创建缓存条目（取最后K次访问时间）
                CacheEntry new_entry;
                new_entry.access_times = deque<time_t>(
                    entry.access_times.end() - k, 
                    entry.access_times.end()
                );
                new_entry.kth_access_time = new_entry.access_times.front();

                // 缓存已满时执行淘汰
                if (cache_map.size() >= capacity) {
                    evict();
                }

                // 加入缓存结构
                cache_map[key] = new_entry;
                cache_tree.insert({new_entry.kth_access_time, key});
                
                // 从历史记录中移除
                history_map.erase(hist_it);
            }
            return;
        }

        // 情况3：新键，加入历史记录
        HistoryEntry new_entry;
        new_entry.access_count = 1;
        new_entry.access_times.push_back(current_time);
        history_map[key] = new_entry;
    }

private:
    // 淘汰缓存中第K次访问时间最早的条目
    void evict() {
        if (!cache_tree.empty()) {
            auto it = cache_tree.begin();
            cache_map.erase(it->second);
            cache_tree.erase(it);
        }
    }
};

// 各数据结构功能说明：
// 1. history_map：哈希表，存储未达K次访问的页面
//   - Key: 页面标识
//   - Value: 历史访问次数和时间戳队列
// 2. cache_map：哈希表，存储已达K次访问的页面
//   - Key: 页面标识
//   - Value: 最近K次访问时间及淘汰依据时间
// 3. cache_tree：红黑树，维护缓存页面的淘汰顺序
//   - 按第K次访问时间排序，实现快速查找最早条目
//   - pair<time_t, int>：时间戳与页面标识组合键

// 算法特性：
// 1. 时间复杂度：访问操作O(logN)（红黑树插入/删除）
// 2. 空间复杂度：O(C)（C为缓存容量）
// 3. 淘汰策略：优先淘汰第K次访问时间最早的缓存页面



/*

#include <unordered_map>
#include <deque>
#include <set>
#include <ctime>

using namespace std;

// 前向声明比较器
template<typename K>
struct CacheKeyComparator;

template<typename K>
class LRUKCache {
private:
    // 历史记录条目结构
    struct HistoryEntry {
        int access_count;
        deque<time_t> access_times;
    };

    // 缓存条目结构
    struct CacheEntry {
        deque<time_t> access_times;
        time_t kth_access_time;
    };

    int k;                   // 访问次数阈值
    size_t capacity;         // 缓存容量
    time_t current_time;     // 模拟时间戳

    // 核心数据结构
    unordered_map<K, HistoryEntry> history_map;     // 未达标访问记录
    unordered_map<K, CacheEntry> cache_map;         // 缓存条目存储
    set<pair<time_t, K>, CacheKeyComparator<K>> cache_tree; // 淘汰顺序索引

public:
    // 构造函数（需要显式指定比较器）
    explicit LRUKCache(int k, size_t capacity)
        : k(k), capacity(capacity), current_time(0),
          cache_tree(CacheKeyComparator<K>()) {}

    void access(const K& key) {
        current_time++;

        // 情况1：存在于缓存
        if (auto cache_it = cache_map.find(key); cache_it != cache_map.end()) {
            handle_cache_hit(key, cache_it->second);
            return;
        }

        // 情况2：存在于历史记录
        if (auto hist_it = history_map.find(key); hist_it != history_map.end()) {
            handle_history_update(key, hist_it->second);
            return;
        }

        // 情况3：全新键
        add_new_history_entry(key);
    }

private:
    // 缓存命中处理
    void handle_cache_hit(const K& key, CacheEntry& entry) {
        // 更新时间队列
        entry.access_times.push_back(current_time);
        if (entry.access_times.size() > k) {
            entry.access_times.pop_front();
        }

        // 更新淘汰索引
        time_t old_time = entry.kth_access_time;
        entry.kth_access_time = entry.access_times.front();
        
        cache_tree.erase({old_time, key});
        cache_tree.insert({entry.kth_access_time, key});
    }

    // 历史记录更新处理
    void handle_history_update(const K& key, HistoryEntry& entry) {
        entry.access_count++;
        entry.access_times.push_back(current_time);

        if (entry.access_count >= k) {
            promote_to_cache(key, entry);
            history_map.erase(key);
        }
    }

    // 提升到缓存
    void promote_to_cache(const K& key, const HistoryEntry& entry) {
        // 创建缓存条目
        CacheEntry new_entry;
        new_entry.access_times = deque<time_t>(
            entry.access_times.end() - k,
            entry.access_times.end()
        );
        new_entry.kth_access_time = new_entry.access_times.front();

        // 执行淘汰（如果需要）
        if (cache_map.size() >= capacity) {
            evict();
        }

        // 插入新条目
        cache_map.emplace(key, new_entry);
        cache_tree.insert({new_entry.kth_access_time, key});
    }

    // 添加新历史记录
    void add_new_history_entry(const K& key) {
        history_map[key] = {1, {current_time}};
    }

    // 淘汰机制
    void evict() {
        if (!cache_tree.empty()) {
            auto it = cache_tree.begin();
            cache_map.erase(it->second);
            cache_tree.erase(it);
        }
    }
};

// 自定义比较器（需前向声明）
template<typename K>
struct CacheKeyComparator {
    bool operator()(const pair<time_t, K>& a, const pair<time_t, K>& b) const {
        // 优先比较时间戳，其次比较键本身
        return (a.first != b.first) ? (a.first < b.first) : (a.second < b.second);
    }
};

// 模板特化说明：
// 1. 键类型K需要满足：
//   - 可哈希（用于unordered_map）
//   - 可比较（用于set中的排序）
//   - 可拷贝构造（存储在pair中）
// 2. 时间戳仍使用time_t类型保持简单性
// 3. 比较器确保相同时间戳的不同键能正确排序



*/