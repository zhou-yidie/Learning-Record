#ifndef NODE_H
#define NODE_H

template<typename K, typename V>
class SkipListPro;  // 前置声明

template<typename K, typename V>
class Node {
    friend class SkipListPro<K, V>;
public:
    Node(K k, V v, int level);
    ~Node();
    
    K getKey() const;
    V getValue() const;
    Node<K, V>** forward;
    int nodeLevel;

private:
    K key;
    V value;
};

template<typename K, typename V>
Node<K, V>::Node(K k, V v, int level) : 
    key(k), value(v), nodeLevel(level) {
    forward = new Node<K, V>*[level + 1]();
    for (int i = 0; i <= level; ++i) {  // 显式初始化指针数组
        forward[i] = nullptr;
    }
}

template<typename K, typename V>
Node<K, V>::~Node() {
    delete[] forward;
}

template<typename K, typename V>
K Node<K, V>::getKey() const { 
    return key; 
}

template<typename K, typename V>
V Node<K, V>::getValue() const { 
    return value; 
}

#endif // NODE_H
