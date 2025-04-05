#include "fiber.h"
#include <vector>
#include <thread>
#include <iostream>

const int THREAD_NUM = 2;
const int FIBER_PER_THREAD = 3;
const int ITERATIONS = 2;

void threadEntry(int thread_id) {
    std::vector<sylar::Fiber::ptr> fibers;
    
    // 显式捕获thread_id和fibers（使用[=]）
    for (int i = 0; i < FIBER_PER_THREAD; ++i) {
        int fiber_id = thread_id * 100 + i;
        fibers.push_back(std::make_shared<sylar::Fiber>(
            [=]() mutable { // 使用mutable允许修改拷贝的变量
                for (int j = 0; j < ITERATIONS; ++j) {
                    std::cout << "==> [" << std::this_thread::get_id() << "] "
                              << "Fiber(" << fiber_id << ") Iter " << j
                              << std::endl;
                    
                    int next_idx = (i + 1) % FIBER_PER_THREAD; // 避免捕获i
                    sylar::Fiber::GetThis()->yieldTo(fibers[next_idx].get());
                }
                std::cout << "==> [" << std::this_thread::get_id() << "] "
                          << "Fiber(" << fiber_id << ") Done"
                          << std::endl;
            },
            fiber_id
        ));
    }

    fibers[0]->resume();
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_NUM; ++i) {
        threads.emplace_back(threadEntry, i);
    }
    for (auto& t : threads) t.join();

    std::cout << "\nMain: All threads completed" << std::endl;
    return 0;
}
