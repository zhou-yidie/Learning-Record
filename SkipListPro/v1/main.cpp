#include <iostream>
#include <chrono>
#include <cstdlib>
#include <pthread.h>
#include <time.h>
#include "SkipList.h"

#define NUM_THREADS 1000
#define TEST_COUNT 100000
SkipList<int, std::string> skipList(18);

void *insertElement(void* threadid) {
    long tid = (long)threadid;
    int tmp = TEST_COUNT / NUM_THREADS; 
    for (int i = tid * tmp, count = 0; count < tmp; ++i, ++count) {
        skipList.insert(i, "a");
    }
    pthread_exit(NULL);
}

void *getElement(void* threadid) {
    long tid = (long)threadid;
    int tmp = TEST_COUNT / NUM_THREADS; 
    for (int i = tid * tmp, count = 0; count < tmp; ++i, ++count) {
        Node<int, std::string> *node = skipList.search(i);
    }
    pthread_exit(NULL);
}

void *removeElement(void* threadid) {
    long tid = (long)threadid;
    int tmp = TEST_COUNT / NUM_THREADS; 
    std::string value;
    for (int i = tid * tmp, count = 0; count < tmp; ++i, ++count) {
        skipList.remove(i, value);
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    pthread_t threads[NUM_THREADS];

    // Insert Test
    auto start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, insertElement, (void*)i);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Insert elapsed: " << elapsed.count() << "s\n";

    // Search Test
    start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, getElement, (void*)i);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Search elapsed: " << elapsed.count() << "s\n";

    // Remove Test
    start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, removeElement, (void*)i);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "Remove elapsed: " << elapsed.count() << "s\n";

    return 0;
}
