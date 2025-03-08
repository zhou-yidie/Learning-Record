#ifndef NODE_H
#define NODE_H

#include <atomic>

// 前置声明 SkipListPro 类
template<typename K, typename V>
class SkipListPro;

// 跳表节点类
template<typename K, typename V>
class Node {
    // 声明 SkipListPro 为友元类，以便其可以访问 Node 的私有成员
    friend class SkipListPro<K, V>;
public:
    // 构造函数，初始化节点的键、值和层级
    Node(K k, V v, int level) : key(k), value(v), nodeLevel(level) {
        // 为 forward 数组分配内存，用于存储指向下一个节点的指针
        forward = new std::atomic<Node<K, V>*>[level + 1];
        // 初始化 forward 数组的每个元素为 nullptr
        for (int i = 0; i <= level; ++i) {
            forward[i].store(nullptr, std::memory_order_relaxed);
        }
    }

    // 析构函数，释放 forward 数组的内存
    ~Node() {
        delete[] forward;
    }

    // 获取节点的键
    K getKey() const {
        return key;
    }

    // 获取节点的值
    V getValue() const {
        return value;
    }

private:
    K key;  // 节点的键
    V value;  // 节点的值
    std::atomic<Node<K, V>*>* forward;  // 指向下一个节点的指针数组
    int nodeLevel;  // 节点所在的层级
};

#endif // NODE_H
