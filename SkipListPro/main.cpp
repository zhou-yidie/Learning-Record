#include <iostream>
#include <chrono>
#include <cstdlib>
#include <pthread.h>
#include <time.h>
#include "SkipList.h"

#define NUM_THREADS 4  // 线程数量
#define TEST_COUNT 100000  // 测试次数
SkipList<int, std::string> skipList(18);

// 插入元素的线程函数
void *insertElement(void* threadid) {
    long tid; 
    tid = (long)threadid;
    std::cout << "Insert Thread ID: " << tid << std::endl;  
    int tmp = TEST_COUNT / NUM_THREADS; 
    for (int i = tid * tmp, count = 0; count < tmp; i++) {
        count++;
        skipList.insert(i, "a"); 
    }
    pthread_exit(NULL);
}

// 查找元素的线程函数
void *getElement(void* threadid) {
    long tid; 
    tid = (long)threadid;
    std::cout << "Search Thread ID: " << tid << std::endl;  
    int tmp = TEST_COUNT / NUM_THREADS; 
    for (int i = tid * tmp, count = 0; count < tmp; i++) {
        count++;
        skipList.search(i); 
    }
    pthread_exit(NULL);
}

// 删除元素的线程函数
void *removeElement(void* threadid) {
    long tid; 
    tid = (long)threadid;
    std::cout << "Remove Thread ID: " << tid << std::endl;  
    int tmp = TEST_COUNT / NUM_THREADS; 
    std::string value;
    for (int i = tid * tmp, count = 0; count < tmp; i++) {
        count++;
        skipList.remove(i, value); 
    }
    pthread_exit(NULL);
}

int main() {
    srand (time(NULL));  

    // 插入测试
    {
        pthread_t threads[NUM_THREADS];
        int rc;
        int i;

        auto start = std::chrono::high_resolution_clock::now();

        for (i = 0; i < NUM_THREADS; i++) {
            std::cout << "main() : creating insert thread, " << i << std::endl;
            rc = pthread_create(&threads[i], NULL, insertElement, (void *)i);

            if (rc) {
                std::cout << "Error: unable to create thread," << rc << std::endl;
                exit(-1);
            }
        }

        void *ret;
        for (i = 0; i < NUM_THREADS; i++) {
            if (pthread_join(threads[i], &ret) != 0)  {
                perror("pthread_create() error"); 
                exit(3);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Insert elapsed: " << elapsed.count() << " seconds" << std::endl;
    }

    // 查找测试
    {
        pthread_t threads[NUM_THREADS];
        int rc;
        int i;

        auto start = std::chrono::high_resolution_clock::now();

        for (i = 0; i < NUM_THREADS; i++) {
            std::cout << "main() : creating search thread, " << i << std::endl;
            rc = pthread_create(&threads[i], NULL, getElement, (void *)i);

            if (rc) {
                std::cout << "Error: unable to create thread," << rc << std::endl;
                exit(-1);
            }
        }

        void *ret;
        for (i = 0; i < NUM_THREADS; i++) {
            if (pthread_join(threads[i], &ret) != 0)  {
                perror("pthread_create() error"); 
                exit(3);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Search elapsed: " << elapsed.count() << " seconds" << std::endl;
    }

    // 删除测试
    {
        pthread_t threads[NUM_THREADS];
        int rc;
        int i;

        auto start = std::chrono::high_resolution_clock::now();

        for (i = 0; i < NUM_THREADS; i++) {
            std::cout << "main() : creating remove thread, " << i << std::endl;
            rc = pthread_create(&threads[i], NULL, removeElement, (void *)i);

            if (rc) {
                std::cout << "Error: unable to create thread," << rc << std::endl;
                exit(-1);
            }
        }

        void *ret;
        for (i = 0; i < NUM_THREADS; i++) {
            if (pthread_join(threads[i], &ret) != 0)  {
                perror("pthread_create() error"); 
                exit(3);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "Remove elapsed: " << elapsed.count() << " seconds" << std::endl;
    }

    pthread_exit(NULL);
    return 0;
}