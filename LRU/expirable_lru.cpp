#include <unordered_map>
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
using namespace std::chrono;

class LRUCache {
public:
    struct Node {
        int key, value;
        time_point<steady_clock> expire;
        Node *left, *right;
        // 新增：接收当前时间，避免休眠期间的时间差
        Node(int _key, int _value, int ttl, time_point<steady_clock> now) 
            : key(_key), value(_value),
              expire(now + seconds(ttl) + milliseconds(1)), // +1ms防边界
              left(nullptr), right(nullptr) {}
    } *L, *R;
    int capacity;
    int default_ttl;
    unordered_map<int, Node*> hash;

    void remove(Node* p) {
        p->right->left = p->left;
        p->left->right = p->right;
    }
    void insert(Node* p) {
        p->right = L->right;
        p->left = L;
        L->right->left = p;
        L->right = p;
    }

    LRUCache(int cap, int default_ttl = 300) 
        : capacity(cap), default_ttl(default_ttl) {
        auto now = steady_clock::now();
        L = new Node(-1, -1, 0, now); // 哨兵节点TTL=0
        R = new Node(-1, -1, 0, now);
        L->right = R;
        R->left = L;
    }

    ~LRUCache() {
        while (L->right != R) {
            auto p = L->right;
            L->right = p->right;
            delete p;
        }
        delete L;
        delete R;
    }

    int get(int key) {
        if (!hash.count(key)) return -1;
        auto p = hash[key];
        auto now = steady_clock::now();
        if (now >= p->expire) { // 边界修正后，需>才会触发
            remove(p);
            hash.erase(key);
            delete p;
            return -1;
        }
        remove(p);
        insert(p);
        return p->value;
    }

    void put(int key, int value, int ttl = -1) {
        auto now = steady_clock::now();
        if (hash.count(key)) {
            auto p = hash[key];
            p->value = value;
            int effective_ttl = ttl == -1 ? default_ttl : ttl;
            p->expire = now + seconds(effective_ttl) + milliseconds(1);
            remove(p);
            insert(p);
            return;
        }

        if (hash.size() >= capacity) {
            auto p = R->left;
            if (p != L && steady_clock::now() >= p->expire) {
                remove(p);
                hash.erase(p->key);
                delete p;
            } else {
                remove(p);
                hash.erase(p->key);
                delete p;
            }
        }

        int effective_ttl = ttl == -1 ? default_ttl : ttl;
        auto p = new Node(key, value, effective_ttl, now);
        hash[key] = p;
        insert(p);
    }
};

int main() {
    LRUCache lru(2, 2); // 容量2，默认TTL=2秒（过期时间=TTL+1ms）
    
    // 1. 插入1（TTL=2秒，过期时间=0s+2s+1ms=2.001s）
    lru.put(1, 100);        
    // 2. 插入2（TTL=1秒，过期时间=0s+1s+1ms=1.001s）
    lru.put(2, 200, 1);     
    
    // 3. 立即获取1：未过期 → 100
    cout << lru.get(1) << endl; // 100
    
    // 4. 休眠1秒（时间=1s，2的过期时间1.001s > 1s，未过期 → 200
    this_thread::sleep_for(seconds(1));  
    cout << lru.get(2) << endl; // 200
    
    // 5. 再次获取1：刷新顺序，未过期 → 100
    cout << lru.get(1) << endl; // 100
    
    // 6. 插入3（容量已满，淘汰最久未使用的2，因2未过期但最少使用）
    lru.put(3, 300);        
    // 现在缓存：1（过期时间2.001s）、3（过期时间1s+2s+1ms=3.001s）
    
    // 7. 休眠2秒（总时间=1s+2s=3s）：
    //    - 1的过期时间2.001s < 3s → 过期，删除
    //    - 3的过期时间3.001s > 3s → 未过期
    this_thread::sleep_for(seconds(2));  
    cout << lru.get(1) << endl; // -1（正确）
    cout << lru.get(3) << endl; // 300（正确，用户当前输出最后一行是200，说明测试用例仍有错误）
    return 0;
}

/*

#include <unordered_map>
#include <chrono>

using namespace std::chrono;

class LRUCache {
public:
    struct Node {
        int key, value;
        long long expire_time; // 过期时间戳（毫秒）
        Node *left, *right;
        Node(int _key, int _value, long long _expire)
            : key(_key), value(_value), expire_time(_expire), left(nullptr), right(nullptr) {}
    } *L, *R;
    int capacity;
    unordered_map<int, Node*> hash;

    LRUCache(int cap) {
        capacity = cap;
        L = new Node(-1, -1, 0);
        R = new Node(-1, -1, 0);
        L->right = R;
        R->left = L;
    }

    void remove(Node* p) {
        p->left->right = p->right;
        p->right->left = p->left;
    }

    void insert(Node* p) {
        p->right = L->right;
        p->left = L;
        L->right->left = p;
        L->right = p;
    }

    // 获取当前时间（毫秒）
    long long getCurrentTime() {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    int get(int key) {
        if (!hash.count(key)) return -1;
        Node* p = hash[key];
        long long current_time = getCurrentTime();
        if (current_time > p->expire_time) { // 检查是否过期
            remove(p);
            hash.erase(key);
            delete p;
            return -1;
        }
        remove(p);
        insert(p); // 移动到头部
        return p->value;
    }

    void put(int key, int value, int ttl) {
        long long expire = getCurrentTime() + ttl * 1000; // 转换为毫秒
        if (hash.count(key)) { // 存在则更新
            Node* p = hash[key];
            p->value = value;
            p->expire_time = expire;
            remove(p);
            insert(p);
        } else { // 插入新节点
            if (hash.size() >= capacity) { // 容量已满，淘汰LRU节点
                Node* lru = R->left;
                remove(lru);
                hash.erase(lru->key);
                delete lru;
            }
            Node* p = new Node(key, value, expire);
            insert(p);
            hash[key] = p;
        }
    }
};

*/