#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

/**
 * 标准布隆过滤器实现
 * @特性: 基础版本，支持插入和存在性检查
 * @适用场景: 静态数据集、只读缓存
 */
template <typename T>
class StandardBloomFilter {
private:
    std::vector<bool> bits;      // 位数组
    size_t hash_count;           // 哈希函数数量
    size_t bit_size;             // 位数组大小

    // 计算最优位数组大小
    static size_t calculateBitSize(size_t n, double p) {
        return static_cast<size_t>(-n * log(p) / (log(2) * log(2)));
    }

    // 计算最优哈希函数数量
    static size_t calculateHashCount(double p) {
        return static_cast<size_t>(-log(p) / log(2));
    }

    // 生成第i个哈希值（双重哈希法）
    size_t hash(const T& key, size_t i) const {
        size_t h1 = std::hash<T>{}(key);
        size_t h2 = std::hash<size_t>{}(h1 + i);
        return (h1 + i * h2) % bit_size;
    }

public:
    /**
     * 构造函数
     * @param expected_elements 预期存储元素数量
     * @param false_positive_prob 可接受的误判概率
     */
    StandardBloomFilter(size_t expected_elements, double false_positive_prob)
        : hash_count(calculateHashCount(false_positive_prob)),
          bit_size(calculateBitSize(expected_elements, false_positive_prob)),
          bits(bit_size, false) {}

    // 插入元素
    void insert(const T& key) {
        for (size_t i = 0; i < hash_count; ++i) {
            bits[hash(key, i)] = true;
        }
    }

    // 检查元素是否存在
    bool contains(const T& key) const {
        for (size_t i = 0; i < hash_count; ++i) {
            if (!bits[hash(key, i)]) return false;
        }
        return true;
    }
};

// 测试用例
void testStandardBloom() {
    StandardBloomFilter<std::string> filter(100, 0.01);
    
    filter.insert("apple");
    filter.insert("orange");
    
    std::cout << "Standard Bloom Filter Test:\n";
    std::cout << "Contains apple? " << filter.contains("apple") << "\n";    // 1
    std::cout << "Contains orange? " << filter.contains("orange") << "\n";  // 1
    std::cout << "Contains banana? " << filter.contains("banana") << "\n";  // 0
}

int main() {
    testStandardBloom();
    return 0;
}
