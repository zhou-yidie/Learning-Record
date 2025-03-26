#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <atomic>


class ThreadPool {
public:
    ThreadPool(int numThreads): stop(false) {
        for (int i = 0; i < numThreads; ++i) {
            workers.push_back(std::thread([this](){
                while (1) {
                    std::function<void()> task;
                    {
                        std::unique_lock lock(queueMutex);
                        /* 	wait函数执行步骤：
                        	1、判断条件：若满足直接返回，不满足沉睡 
                            2、被唤醒，回到步骤1	
                        */
                        condition.wait(lock, [&](){ return stop || !tasks.empty(); }); 
                        if (stop && tasks.empty()) {
                            std::cout << "Thread " << std::this_thread::get_id() << " has finished." << std::endl;
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            }));
        }
    }

    ~ThreadPool() {
        stop = true;
        condition.notify_all(); //唤醒所有线程，逐个获得锁进行if (stop && tasks.empty())判断
        for (std::thread &worker : workers) {
            worker.join();
        }
    }

    void enqueue(std::function<void()> task) {
        std::unique_lock lock(queueMutex);
        tasks.push(std::move(task));
        condition.notify_one();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};


void exampleTask(int id) {
    std::cout << "Task " << id << " is being processed by thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    ThreadPool pool(3);  // 创建包含3个线程的线程池

    for (int i = 0; i < 10; ++i) {
        pool.enqueue([i](){ //传入一个任务
            exampleTask(i);
        });
    }
}
