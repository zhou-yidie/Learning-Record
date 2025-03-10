#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <memory>

/**
 * 动态扩容布隆过滤器
 * @特性: 自动扩展容量，适应数据增长
 * @机制: 分层存储，后续层使用更严格的误判率
 */
template <typename T>
class ScalableBloomFilter {
private:
    struct FilterLayer {
        std::vector<bool> bits;
        size_t hash_count;
        size_t bit_size;
        double fp_prob;

        FilterLayer(size_t n, double p)
            : hash_count(static_cast<size_t>(-log(p) / log(2))),
              bit_size(static_cast<size_t>(-n * log(p) / (log(2) * log(2)))),
              fp_prob(p),
              bits(bit_size, false) {}
    };

    std::vector<FilterLayer> layers;
    size_t initial_size;
    double growth_factor;
    double fp_decay;

    // 生成哈希值（包含层数作为随机种子）
    size_t hash(const T& key, size_t i, const FilterLayer& layer) const {
        size_t h1 = std::hash<T>{}(key);
        size_t h2 = std::hash<size_t>{}(h1 + i + layer.bit_size);
        return (h1 + i * h2) % layer.bit_size;
    }

public:
    /**
     * 构造函数
     * @param initial_capacity 初始容量
     * @param initial_fp 初始层误判率
     * @param growth 容量增长因子（>1）
     * @param fp_decay 误判率衰减因子（<1）
     */
    ScalableBloomFilter(size_t initial_capacity = 1000,
                       double initial_fp = 0.01,
                       double growth = 2.0,
                       double fp_decay = 0.5)
        : initial_size(initial_capacity),
          growth_factor(growth),
          fp_decay(fp_decay) {
        addLayer(initial_fp);
    }

    // 添加新层
    void addLayer(double current_fp) {
        size_t layer_size = initial_size * pow(growth_factor, layers.size());
        layers.emplace_back(layer_size, current_fp);
    }

    // 插入元素（自动扩容）
    void insert(const T& key) {
        // 检查是否需要扩容
        if (layers.back().fp_prob < 1e-6 || contains(key)) {
            addLayer(layers.back().fp_prob * fp_decay);
        }
        
        // 插入最新层
        auto& layer = layers.back();
        for (size_t i = 0; i < layer.hash_count; ++i) {
            layer.bits[hash(key, i, layer)] = true;
        }
    }

    // 存在性检查（逐层检查）
    bool contains(const T& key) const {
        for (const auto& layer : layers) {
            bool found = true;
            for (size_t i = 0; i < layer.hash_count; ++i) {
                if (!layer.bits[hash(key, i, layer)]) {
                    found = false;
                    break;
                }
            }
            if (found) return true;
        }
        return false;
    }
};

// 测试用例
void testScalableBloom() {
    ScalableBloomFilter<double> filter;
    
    for (int i = 0; i < 1000; ++i) {
        filter.insert(i * 1.0);
    }
    
    std::cout << "\nScalable Bloom Filter Test:\n";
    std::cout << "Contains 500.0? " << filter.contains(500.0) << "\n"; // 1
    std::cout << "Contains 999.0? " << filter.contains(999.0) << "\n"; // 1
    std::cout << "False positive? " << filter.contains(-1.0) << "\n";  // 0
}

int main() {
    testScalableBloom();
    return 0;
}
