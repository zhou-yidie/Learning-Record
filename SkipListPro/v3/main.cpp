#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "SkipListPro.h"

#define NUM_THREADS 4
#define OPERATIONS 100000

SkipListPro<int, std::string> skiplist;

void concurrentInsert(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        skiplist.insert(i, "data_" + std::to_string(i));
    }
}

void concurrentSearch(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        auto val = skiplist.search(i);
        if (val != "data_" + std::to_string(i)) {
            std::cerr << "Error: Invalid value at " << i << std::endl;
        }
    }
}

void concurrentDelete(int start) {
    for (int i = start; i < start + OPERATIONS; ++i) {
        if (!skiplist.remove(i)) {
            std::cerr << "Error: Delete failed at " << i << std::endl;
        }
    }
}

int main() {
    // 插入测试
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(concurrentInsert, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Insert done. Time: " << duration.count() << "ms. Size: " 
              << skiplist.size() << std::endl;

    // 查询测试
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(concurrentSearch, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Search done. Time: " << duration.count() << "ms" << std::endl;

    // 删除测试
    threads.clear();
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(concurrentDelete, i * OPERATIONS);
    }
    for (auto& t : threads) t.join();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Delete done. Time: " << duration.count() << "ms. Final size: " 
              << skiplist.size() << std::endl;

    return 0;
}
