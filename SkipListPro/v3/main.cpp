#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include "SkipListPro.h"

#define NUM_THREADS 5
#define OPERATIONS 200000

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

// 计算并输出 QPS 的辅助函数
void calculateAndPrintQPS(const std::string& operation, const std::chrono::milliseconds& duration, int totalOperations) {
    double seconds = duration.count() / 1000.0;
    double qps = totalOperations / seconds;
    std::cout << operation << " QPS: " << qps << std::endl;
}

int main() {
    // 插入测试
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testInsert, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto insertDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    int totalInsertOperations = NUM_THREADS * OPERATIONS;
    std::cout << "Insert completed. Time: " << insertDuration.count() 
              << "ms | Size: " << skiplist.size() << std::endl;
    calculateAndPrintQPS("Insert", insertDuration, totalInsertOperations);

    // 查询测试
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testSearch, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    auto searchDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    int totalSearchOperations = NUM_THREADS * OPERATIONS;
    std::cout << "Search completed. Time: " << searchDuration.count() << "ms" << std::endl;
    calculateAndPrintQPS("Search", searchDuration, totalSearchOperations);

    // 删除测试
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(testRemove, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    end = std::chrono::high_resolution_clock::now();
    auto removeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    int totalRemoveOperations = NUM_THREADS * OPERATIONS;
    std::cout << "Remove completed. Time: " << removeDuration.count() 
              << "ms | Final Size: " << skiplist.size() << std::endl;
    calculateAndPrintQPS("Remove", removeDuration, totalRemoveOperations);

    return 0;
}
