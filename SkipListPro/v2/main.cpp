#include <iostream>
#include <chrono>
#include <cstdlib>
#include <pthread.h>
#include "SkipList.h"

#define NUM_THREADS 1000
#define TEST_COUNT 100000
SkipList<int, std::string> skipList(1000000);

void* insertElement(void* arg) {
    long tid = (long)arg;
    int batch = TEST_COUNT / NUM_THREADS;
    for (int i = tid * batch; i < (tid + 1) * batch; ++i) {
        skipList.insert(i, "v");
    }
    return nullptr;
}

void* searchElement(void* arg) {
    long tid = (long)arg;
    int batch = TEST_COUNT / NUM_THREADS;
    for (int i = tid * batch; i < (tid + 1) * batch; ++i) {
        skipList.search(i);
    }
    return nullptr;
}

void* removeElement(void* arg) {
    long tid = (long)arg;
    int batch = TEST_COUNT / NUM_THREADS;
    std::string tmp;
    for (int i = tid * batch; i < (tid + 1) * batch; ++i) {
        skipList.remove(i, tmp);
    }
    return nullptr;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Insert Test
    auto start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], nullptr, insertElement, (void*)i);
    for (auto& th : threads) pthread_join(th, nullptr);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Insert time: " << duration.count() << "ms\n";

    // Search Test
    start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], nullptr, searchElement, (void*)i);
    for (auto& th : threads) pthread_join(th, nullptr);
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Search time: " << duration.count() << "ms\n";

    // Remove Test
    start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], nullptr, removeElement, (void*)i);
    for (auto& th : threads) pthread_join(th, nullptr);
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start
    );
    std::cout << "Remove time: " << duration.count() << "ms\n";

    return 0;
}