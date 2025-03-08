#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "SkipListPro.h"

#define NUM_THREADS 4
#define OPERATIONS 100000

SkipListPro<int, std::string> skiplist;

void testInsert(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        skiplist.insert(i, "data_" + std::to_string(i));
    }
}

void testSearch(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        skiplist.search(i);
    }
}

void testRemove(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        skiplist.remove(i);
    }
}

int main() {
    // 插入测试
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testInsert, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Insert completed. Time: " << duration.count() 
              << "ms | Size: " << skiplist.size() << std::endl;

    // 查询测试
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testSearch, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Search completed. Time: " << duration.count() << "ms" << std::endl;

    // 删除测试（关键修复）
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    std::cout << "Delete phase start" << std::endl;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testRemove, i * OPERATIONS);
    }
    std::cout << "All remove threads started" << std::endl;
    for (auto& t : threads) t.join();
    std::cout << "All remove threads joined" << std::endl;
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Remove completed. Time: " << duration.count() 
              << "ms | Final Size: " << skiplist.size() << std::endl;

    return 0;
}
