#ifndef NODE_H
#define NODE_H

#include <atomic>

// 跳表节点
template<typename K, typename V>
class Node {
public:
    // 构造函数
    Node(K key, V value, int level) : key(key), value(value), nodeLevel(level) {
        forward = new std::atomic<Node<K, V>*>[level + 1];
        for (int i = 0; i <= level; ++i) {
            forward[i].store(nullptr);
        }
    }

    // 析构函数
    ~Node() {
        delete[] forward;
    }

    // 获取键值
    K getKey() const {
        return key;
    }

    // 获取值
    V getValue() const {
        return value;
    }

    // 前进指针数组
    std::atomic<Node<K, V>*>* forward;
    // 节点层级
    int nodeLevel;

private:
    K key;
    V value;
};

#endif // NODE_H
