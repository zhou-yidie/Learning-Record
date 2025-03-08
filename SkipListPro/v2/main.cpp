#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "SkipListPro.h"  // 确保包含该头文件

#define NUM_THREADS 4
#define OPERATIONS 250000

SkipListPro<int, std::string> skiplist;

// 插入测试函数
void testInsert(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        skiplist.insert(i, "data_" + std::to_string(i));
    }
}

// 查找测试函数
void testSearch(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        skiplist.search(i);
    }
}

// 删除测试函数
void testRemove(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        skiplist.remove(i);
    }
}

int main() {
    std::vector<std::thread> threads;

    // 插入测试
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testInsert, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Insert completed. Time: " << duration.count() 
              << "ms | Size: " << skiplist.size() << std::endl;

    // 查找测试
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testSearch, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Search completed. Time: " << duration.count() << "ms" << std::endl;

    // 删除测试
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testRemove, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Remove completed. Time: " << duration.count() 
              << "ms | Final Size: " << skiplist.size() << std::endl;

    return 0;
}
