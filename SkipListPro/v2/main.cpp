#include "SkipListPro.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // 创建一个跳表实例，最大索引层数设为 16（即总层数 17）
    SkipList<int, std::string> skiplist(16);
    
    // 插入 50 个元素
    for (int i = 1; i <= 50; i++) {
        skiplist.insert_element(i, "val" + std::to_string(i));
    }
    std::cout << "跳表插入后结构：" << std::endl;
    skiplist.display_list();
    
    // 调用重平衡检查函数
    skiplist.rebalance();
    std::cout << "\n重平衡后结构：" << std::endl;
    skiplist.display_list();
    
    // 测试查找功能
    std::string value;
    if (skiplist.search_element(25, value)) {
        std::cout << "\n搜索到 key 25, value: " << value << std::endl;
    } else {
        std::cout << "\n未搜索到 key 25" << std::endl;
    }
    
    // 测试删除功能
    skiplist.delete_element(25);
    std::cout << "\n删除 key 25 后结构：" << std::endl;
    skiplist.display_list();
    
    // 性能测试：插入大量数据并调用重平衡
    SkipList<int, std::string> largeSkipList(16);
    const int N = 100000;
    auto start = std::chrono::steady_clock::now();
    for (int i = 1; i <= N; i++) {
        largeSkipList.insert_element(i, "val" + std::to_string(i));
    }
    auto mid = std::chrono::steady_clock::now();
    largeSkipList.rebalance();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> insertTime = mid - start;
    std::chrono::duration<double> rebalanceTime = end - mid;
    std::cout << "\n插入 " << N << " 个元素耗时: " << insertTime.count() << " 秒" << std::endl;
    std::cout << "重平衡耗时: " << rebalanceTime.count() << " 秒" << std::endl;
    
    return 0;
}
