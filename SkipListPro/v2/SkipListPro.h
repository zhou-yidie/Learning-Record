#ifndef SKIPLIST_H
#define SKIPLIST_H
/* ************************************************************************
> File Name:     skiplist.h
> Author:        程序员Carl
> 微信公众号:    代码随想录
> Created Time:  Sun Dec  2 19:04:26 2018
> Description:
 ************************************************************************/

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iostream>
#include <sstream>
#include <mutex>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#define STORE_FILE "store/dumpFile"

static std::string delimiter = ":";

// 模板类：跳表节点
template <typename K, typename V>
class Node {
public:
    Node() {}
    Node(const K k, const V v, int level);
    ~Node();

    K get_key() const;
    V get_value() const;
    void set_value(V val);

    // forward 数组保存该节点在各层的后继指针
    Node<K, V> **forward;
    int node_level; // forward 数组长度，即该节点存在的层数

private:
    K key;
    V value;
};

template <typename K, typename V>
Node<K, V>::Node(const K k, const V v, int level)
    : key(k), value(v), node_level(level)
{
    // 分配 level 个指针（层号从 0 到 level-1）
    forward = new Node<K, V>*[level];
    memset(forward, 0, sizeof(Node<K, V>*) * level);
}

template <typename K, typename V>
Node<K, V>::~Node() {
    delete[] forward;
}

template <typename K, typename V>
K Node<K, V>::get_key() const {
    return key;
}

template <typename K, typename V>
V Node<K, V>::get_value() const {
    return value;
}

template <typename K, typename V>
void Node<K, V>::set_value(V val) {
    value = val;
}


// Class template to implement node
template <typename K, typename V>
class SkipListDump {
   public:
    friend class boost::serialization::access;

    template <class Archive>
    [[maybe_unused]] void serialize(Archive &ar, [[maybe_unused]] const unsigned int version) {
        ar & keyDumpVt_;
        ar & valDumpVt_;
    }
    std::vector<K> keyDumpVt_;
    std::vector<V> valDumpVt_;

   public:
    void insert(const Node<K, V> &node);
};

// 模板类：跳表
// 构造时传入的 max_level 表示除底层外允许的最大索引层数，
// 所以头节点的 forward 数组大小为 max_level+1（总层数 = max_level+1，Level0 为底层）。
template <typename K, typename V>
class SkipList {
public:
    // max_level: 除底层外允许的最大索引层数，实际总层数 = max_level+1
    SkipList(int max_level);
    ~SkipList();
    
    int get_random_level();
    Node<K, V>* create_node(const K, const V, int);
    
    // 返回 1 表示键已存在，0 表示插入成功
    int insert_element(const K, const V);
    bool search_element(const K, V &);
    void delete_element(const K);
    void display_list();
    int size();
    void insert_set_element(K &, V &);
    std::string dump_file(); 
    void load_file(const std::string &dumpStr); 
    // 重平衡检查函数：基于 Level0 链均匀采样重建 Level1 ~ max_level 层的索引
    void rebalance();

private:
    // 递归删除节点
    void clear(Node<K, V>*);
    // 重建 header->forward[i]（i>=1）链，重建时仅使用具有足够层级的节点
    void rebuild_index();

    void get_key_value_from_string(const std::string &str, std::string *key, std::string *value);
    bool is_valid_string(const std::string &str);

private:
    int _max_level;         // 除底层外允许的最大索引层数
    int _skip_list_level;   // 当前跳表的最高有效层（下标，从 0 开始，Level0 为底层）
    Node<K, V>* _header;    // 头节点（不存实际数据），其 forward 数组大小为 _max_level+1
    int _element_count;     // 当前元素总数
    std::mutex _mtx;        // 保护跳表操作的互斥锁
    // file operator
    std::ofstream _file_writer;
    std::ifstream _file_reader;
};

template <typename K, typename V>
SkipList<K, V>::SkipList(int max_level)
    : _max_level(max_level), _skip_list_level(0), _element_count(0)
{
    K k{};
    V v{};
    // 头节点分配 _max_level+1 个指针
    _header = new Node<K, V>(k, v, _max_level + 1);
}

template <typename K, typename V>
SkipList<K, V>::~SkipList() {
    std::lock_guard<std::mutex> lock(_mtx);
    if (_header->forward[0] != nullptr) {
        clear(_header->forward[0]);
    }
    delete _header;
}

template <typename K, typename V>
void SkipList<K, V>::clear(Node<K, V>* cur) {
    if(cur->forward[0] != nullptr) {
        clear(cur->forward[0]);
    }
    delete cur;
}

template <typename K, typename V>
int SkipList<K, V>::get_random_level() {
    int lvl = 1;
    while ((rand() % 2) && lvl < _max_level + 1)
        lvl++;
    return lvl;
}

template <typename K, typename V>
Node<K, V>* SkipList<K, V>::create_node(const K k, const V v, int level) {
    Node<K, V>* n = new Node<K, V>(k, v, level);
    return n;
}

template <typename K, typename V>
int SkipList<K, V>::insert_element(const K key, const V value) {
    std::lock_guard<std::mutex> lock(_mtx);
    Node<K, V>* current = _header;
    std::vector<Node<K, V>*> update(_max_level + 1, nullptr);
    for (int i = _skip_list_level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    if (current != nullptr && current->get_key() == key) {
        // std::cout << "key: " << key << ", exists" << std::endl;
        // _mtx.unlock();
        return 1; // 键已存在
    }
    int random_level = get_random_level();
    if (random_level - 1 > _skip_list_level) {
        for (int i = _skip_list_level + 1; i < random_level; i++) {
            update[i] = _header;
        }
        _skip_list_level = random_level - 1;
    }
    Node<K, V>* new_node = create_node(key, value, random_level);
    for (int i = 0; i < random_level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
    // std::cout << "Successfully inserted key:" << key << ", value:" << value << std::endl;
    _element_count++;
    return 0;
}

template <typename K, typename V>
bool SkipList<K, V>::search_element(const K key, V &value) {
    std::lock_guard<std::mutex> lock(_mtx);
    Node<K, V>* current = _header;
    for (int i = _skip_list_level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    if (current != nullptr && current->get_key() == key) {
        value = current->get_value();
        return true;
    }
    return false;
}

template <typename K, typename V>
void SkipList<K, V>::delete_element(const K key) {
    std::lock_guard<std::mutex> lock(_mtx);
    Node<K, V>* current = _header;
    std::vector<Node<K, V>*> update(_max_level + 1, nullptr);
    for (int i = _skip_list_level; i >= 0; i--) {
        while (current->forward[i] != nullptr && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    if (current != nullptr && current->get_key() == key) {
        for (int i = 0; i <= _skip_list_level; i++) {
            if (update[i]->forward[i] != current)
                break;
            update[i]->forward[i] = current->forward[i];
        }
        delete current;
        _element_count--;
        while (_skip_list_level > 0 && _header->forward[_skip_list_level] == nullptr) {
            _skip_list_level--;
        }
    }
}

template <typename K, typename V>
void SkipList<K, V>::display_list() {
    std::lock_guard<std::mutex> lock(_mtx);
    std::cout << "\n***** Skip List *****\n";
    for (int i = 0; i <= _skip_list_level; i++) {
        Node<K, V>* node = _header->forward[i];
        std::cout << "Level " << i << ": ";
        while (node != nullptr) {
            std::cout << node->get_key() << ":" << node->get_value() << " ";
            node = node->forward[i];
        }
        std::cout << std::endl;
    }
}

// todo 对dump 和 load 后面可能要考虑加锁的问题
// Dump data in memory to file
template <typename K, typename V>
std::string SkipList<K, V>::dump_file() {
    // std::cout << "dump_file-----------------" << std::endl;
    //
    //
    // _file_writer.open(STORE_FILE);
    Node<K, V> *node = this->_header->forward[0];
    SkipListDump<K, V> dumper;
    while (node != nullptr) {
        dumper.insert(*node);
        // _file_writer << node->get_key() << ":" << node->get_value() << "\n";
        // std::cout << node->get_key() << ":" << node->get_value() << ";\n";
        node = node->forward[0];
    }
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << dumper;
    return ss.str();
    // _file_writer.flush();
    // _file_writer.close();
}

// Load data from disk
template <typename K, typename V>
void SkipList<K, V>::load_file(const std::string &dumpStr) {
    // _file_reader.open(STORE_FILE);
    // std::cout << "load_file-----------------" << std::endl;
    // std::string line;
    // std::string* key = new std::string();
    // std::string* value = new std::string();
    // while (getline(_file_reader, line)) {
    //     get_key_value_from_string(line, key, value);
    //     if (key->empty() || value->empty()) {
    //         continue;
    //     }
    //     // Define key as int type
    //     insert_element(stoi(*key), *value);
    //     std::cout << "key:" << *key << "value:" << *value << std::endl;
    // }
    // delete key;
    // delete value;
    // _file_reader.close();

    if (dumpStr.empty()) {
        return;
    }
    SkipListDump<K, V> dumper;
    std::stringstream iss(dumpStr);
    boost::archive::text_iarchive ia(iss);
    ia >> dumper;
    for (int i = 0; i < dumper.keyDumpVt_.size(); ++i) {
        insert_element(dumper.keyDumpVt_[i], dumper.keyDumpVt_[i]);
    }
}

template <typename K, typename V>
int SkipList<K, V>::size() {
    std::lock_guard<std::mutex> lock(_mtx);
    return _element_count;
}

template <typename K, typename V>
void SkipList<K, V>::get_key_value_from_string(const std::string &str, std::string *key, std::string *value) {
    if (!is_valid_string(str)) {
        return;
    }
    *key = str.substr(0, str.find(delimiter));
    *value = str.substr(str.find(delimiter) + 1, str.length());
}

template <typename K, typename V>
bool SkipList<K, V>::is_valid_string(const std::string &str) {
    if (str.empty()) {
        return false;
    }
    if (str.find(delimiter) == std::string::npos) {
        return false;
    }
    return true;
}

/**
 * \brief 作用与insert_element相同类似，
 * insert_element是插入新元素，
 * insert_set_element是插入元素，如果元素存在则改变其值
 */
template <typename K, typename V>
void SkipList<K, V>::insert_set_element(K &key, V &value) {
    V oldValue;
    if (search_element(key, oldValue)) {
        delete_element(key);
    }
    insert_element(key, value);
}

// Search for element in skip list
/*
                           +------------+
                           |  select 60 |
                           +------------+
level 4     +-->1+                                                      100
                 |
                 |
level 3         1+-------->10+------------------>50+           70       100
                                                   |
                                                   |
level 2         1          10         30         50|           70       100
                                                   |
                                                   |
level 1         1    4     10         30         50|           70       100
                                                   |
                                                   |
level 0         1    4   9 10         30   40    50+-->60      70       100
*/

template <typename K, typename V>
void SkipListDump<K, V>::insert(const Node<K, V> &node) {
    keyDumpVt_.emplace_back(node.get_key());
    valDumpVt_.emplace_back(node.get_value());
}


// 重建上层索引：从 Level0 链中采集所有节点，然后对于每一层 i (i>=1)
// 只使用那些节点的 node_level > i（即有 i 层以上的节点），并按简单均匀采样（每隔 2 个节点）构建 header->forward[i]
template <typename K, typename V>
void SkipList<K, V>::rebuild_index() {
    // 收集 Level0 链上所有节点（不包括头节点）
    std::vector<Node<K, V>*> level0;
    Node<K, V>* cur = _header->forward[0];
    while (cur != nullptr) {
        level0.push_back(cur);
        cur = cur->forward[0];
    }
    int n = level0.size();
    if (n == 0) return;
    
    // 理想层数 = min(_max_level+1, floor(log2(n)) + 1)
    int ideal_levels = std::max(1, static_cast<int>(std::log2(n)) + 1);
    ideal_levels = std::min(ideal_levels, _max_level + 1);
    _skip_list_level = ideal_levels - 1; // 层号从 0 开始
    
    // 对于每一层 i 从 1 到 ideal_levels-1，重建索引
    for (int lvl = 1; lvl < ideal_levels; lvl++) {
        // 收集 eligible 节点：仅那些 node_level > lvl 的节点
        std::vector<Node<K, V>*> eligible;
        for (auto node : level0) {
            if (node->node_level > lvl) {
                eligible.push_back(node);
            }
        }
        if (eligible.empty()) {
            _header->forward[lvl] = nullptr;
            continue;
        }
        // 简单策略：每隔 2 个 eligible 节点采样一次
        int step = 2;
        _header->forward[lvl] = eligible[0];
        Node<K, V>* prev = eligible[0];
        for (size_t j = step; j < eligible.size(); j += step) {
            prev->forward[lvl] = eligible[j];
            prev = eligible[j];
        }
        prev->forward[lvl] = nullptr;
    }
    // 对于 lvl 从 ideal_levels 到 _max_level, 置 header->forward[lvl] 为 nullptr
    for (int lvl = ideal_levels; lvl < _max_level + 1; lvl++) {
        _header->forward[lvl] = nullptr;
    }
}

template <typename K, typename V>
void SkipList<K, V>::rebalance() {
    std::lock_guard<std::mutex> lock(_mtx);
    rebuild_index();
}

#endif // SKIPLIST_H