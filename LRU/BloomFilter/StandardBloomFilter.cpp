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



/*

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>

/**
 * 标准布隆过滤器实现
 */
/*
template <typename T>
class StandardBloomFilter {
private:
    // 调整成员变量声明顺序，确保正确初始化
    size_t bit_size;            // 位数组大小（单位：bit），必须在 byte_size 之前初始化
    size_t hash_count;          // 哈希函数数量，必须在 bits 之前初始化
    size_t byte_size;           // 位数组字节大小，必须在 bits 之前初始化
    std::vector<uint8_t> bits;  // 用 uint8_t 代替 bool，防止 undefined behavior

    // 计算最优位数组大小（加上限制，避免超大值）
    static size_t calculateBitSize(size_t n, double p) {
        if (p <= 0 || p >= 1) {
            throw std::invalid_argument("Probability must be in (0,1)");
        }
        if (n == 0) {
            throw std::invalid_argument("Elements must be >0");
        }
        constexpr size_t MAX_SIZE = 100000000;  // 限制最大 1 亿 bit（≈12.5MB）
        double size = -n * log(p) / (log(2) * log(2));
        return std::min(static_cast<size_t>(std::ceil(size)), MAX_SIZE);
    }

    // 计算最优哈希函数数量
    static size_t calculateHashCount(double p) {
        return std::max<size_t>(1, static_cast<size_t>(std::ceil(-log(p) / log(2))));
    }

    // 安全哈希函数
    size_t hash(const T& key, size_t i) const {
        size_t h1 = std::hash<T>{}(key);
        size_t h2 = std::hash<size_t>{}(h1 ^ i); // 使用异或增强散列
        return (h1 + i * h2) % bit_size;
    }

public:
    /**
     * 构造函数
     */
    StandardBloomFilter(size_t expected_elements, double false_positive_prob)
            : bit_size(std::max(calculateBitSize(expected_elements, false_positive_prob), size_t(1))),
              hash_count(calculateHashCount(false_positive_prob)),
              byte_size((bit_size + 7) / 8),
              bits(byte_size, 0)
    {
        std::cout << "Initialized with "
                  << bit_size << " bits (" << byte_size << " bytes), "
                  << hash_count << " hash functions\n";
    }

    // 安全插入
    void insert(const T& key) {
        for (size_t i = 0; i < hash_count; ++i) {
            const size_t index = hash(key, i);
            bits[index / 8] |= static_cast<uint8_t>(1) << (index % 8);
        }
    }

    // 安全查询
    bool contains(const T& key) const {
        for (size_t i = 0; i < hash_count; ++i) {
            const size_t index = hash(key, i);
            if ((bits[index / 8] & (static_cast<uint8_t>(1) << (index % 8))) == 0) {
                return false;
            }
        }
        return true;
    }

    // 获取位数组大小
    size_t getBitSize() const {
        return bit_size;
    }

    // 获取哈希函数数量
    size_t getHashCount() const {
        return hash_count;
    }
};

// 基础测试
void testStandardBloom() {
    StandardBloomFilter<std::string> filter(100, 0.01);

    filter.insert("apple");
    filter.insert("orange");

    std::cout << std::boolalpha;
    std::cout << "Contains apple: " << filter.contains("apple") << "\n";    // true
    std::cout << "Contains orange: " << filter.contains("orange") << "\n";  // true
    std::cout << "Contains banana: " << filter.contains("banana") << "\n";  // false
}

// 大数据测试
void testLargeData() {
    const size_t N = 100000; // 10万数据量
    const double FP = 0.01;

    StandardBloomFilter<int> filter(N, FP);

    // 插入数据
    for (int i = 0; i < N; ++i) {
        filter.insert(i);
    }

    // 验证存在性
    size_t found = 0;
    for (int i = 0; i < N; ++i) {
        found += filter.contains(i);
    }
    std::cout << "Found " << found << "/" << N << " inserted items\n";

    // 测试误判
    const size_t TEST_N = 50000;
    size_t false_pos = 0;
    for (int i = N; i < N + TEST_N; ++i) {
        false_pos += filter.contains(i);
    }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "False positive rate: "
              << (false_pos * 100.0 / TEST_N) << "%\n";
}

int main() {
    testStandardBloom();
    std::cout << "test1--------------------------test2\n";
    testLargeData();
    return 0;
}


*/