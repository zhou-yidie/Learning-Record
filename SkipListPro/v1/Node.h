#ifndef SKIPLISTPRO_NODE_H
#define SKIPLISTPRO_NODE_H

template<typename K, typename V>
class SkipList;

template<typename K, typename V>
class Node {
    friend class SkipList<K, V>;
public:
    Node() : forward(nullptr), nodeLevel(0) {}
    Node(K k, V v, int level);
    ~Node();
    K getKey() const;
    V getValue() const;
private:
    K key;
    V value;
    Node<K, V> **forward;
    int nodeLevel;
};

template<typename K, typename V>
Node<K, V>::Node(const K k, const V v, int level) : key(k), value(v), nodeLevel(level) {
    forward = new Node<K, V>*[level + 1];
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

#endif //SKIPLISTPRO_NODE_H
