// Node.h
#ifndef SKIPLISTPRO_NODE_H
#define SKIPLISTPRO_NODE_H

template<typename K, typename V>
class SkipList;

// 跳表节点类
template<typename K, typename V>
class Node {
    friend class SkipList<K, V>;
public:
    Node() {}
    // 构造函数，初始化节点的键和值
    Node(K k, V v);
    // 析构函数，释放节点的 forward 数组
    ~Node();
    // 获取节点的键
    K getKey() const;
    // 获取节点的值
    V getValue() const;
private:
    K key;  // 节点的键
    V value;  // 节点的值
    Node<K, V> **forward;  // 节点的前向指针数组
    int nodeLevel;  // 节点的层级
};

// 节点类的构造函数实现
template<typename K, typename V>
Node<K, V>::Node(const K k, const V v) {
    key = k;
    value = v;
}

// 节点类的析构函数实现
template<typename K, typename V>
Node<K, V>::~Node() {
    delete[] forward;
}

// 获取节点的键
template<typename K, typename V>
K Node<K, V>::getKey() const {
    return key;
}

// 获取节点的值
template<typename K, typename V>
V Node<K, V>::getValue() const {
    return value;
}

#endif //SKIPLISTPRO_NODE_H
