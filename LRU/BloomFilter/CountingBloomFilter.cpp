#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <climits>

/**
 * 计数布隆过滤器实现
 * @特性: 支持删除操作，使用计数器替代二进制位
 * @注意: 计数器溢出可能导致误删
 */
template <typename T>
class CountingBloomFilter {
private:
    std::vector<uint8_t> counters; // 8位计数器数组
    size_t hash_count;
    size_t bit_size;

    // 计算参数方法与标准版相同
    static size_t calculateBitSize(size_t n, double p) {
        return static_cast<size_t>(-n * log(p) / (log(2) * log(2)));
    }

    static size_t calculateHashCount(double p) {
        return static_cast<size_t>(-log(p) / log(2));
    }

    size_t hash(const T& key, size_t i) const {
        size_t h1 = std::hash<T>{}(key);
        size_t h2 = std::hash<size_t>{}(h1 + i);
        return (h1 + i * h2) % bit_size;
    }

public:
    CountingBloomFilter(size_t expected_elements, double false_positive_prob)
        : hash_count(calculateHashCount(false_positive_prob)),
          bit_size(calculateBitSize(expected_elements, false_positive_prob)),
          counters(bit_size, 0) {}

    // 插入元素（增加计数器）
    void insert(const T& key) {
        for (size_t i = 0; i < hash_count; ++i) {
            auto& cnt = counters[hash(key, i)];
            if (cnt < UINT8_MAX) cnt++;
        }
    }

    // 删除元素（减少计数器）
    void remove(const T& key) {
        for (size_t i = 0; i < hash_count; ++i) {
            auto& cnt = counters[hash(key, i)];
            if (cnt > 0) cnt--;
        }
    }

    // 存在性检查
    bool contains(const T& key) const {
        for (size_t i = 0; i < hash_count; ++i) {
            if (counters[hash(key, i)] == 0) return false;
        }
        return true;
    }
};

// 测试用例
void testCountingBloom() {
    CountingBloomFilter<int> filter(100, 0.01);
    
    filter.insert(42);
    filter.insert(42); // 重复插入
    
    std::cout << "\nCounting Bloom Filter Test:\n";
    std::cout << "Contains 42? " << filter.contains(42) << "\n"; // 1
    
    filter.remove(42);
    std::cout << "After 1 remove: " << filter.contains(42) << "\n"; // 1
    filter.remove(42);
    std::cout << "After 2 removes: " << filter.contains(42) << "\n"; // 0
}

int main() {
    testCountingBloom();
    return 0;
}
