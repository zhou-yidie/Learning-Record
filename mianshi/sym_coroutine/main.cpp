#include "fiber.h"
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>

using namespace sylar;

// 测试参数
const int NUM_FIBERS = 3;
const int ITERATIONS = 3;

// -------------------------------
// 对称调度测试（Fiber 间直接切换）
// -------------------------------
std::vector<Fiber::ptr> sym_fibers;

void symmetricFiberFunc(int id) {
    for (int i = 0; i < ITERATIONS; ++i) {
        std::cout << "[Symmetric Fiber " << id << "] iteration " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // 计算下一个 Fiber 的 id，形成循环
        int next = (id + 1) % NUM_FIBERS;
        // 如果下一个 Fiber 尚未结束，则直接切换到它；否则退回主上下文
        if (sym_fibers[next] && !sym_fibers[next]->isFinished()) {
            Fiber::GetThis()->yieldTo(sym_fibers[next].get());
        } else {
            Fiber::GetThis()->yieldToMain();
        }
    }
    std::cout << "[Symmetric Fiber " << id << "] completed" << std::endl;
    // 结束后退回主上下文
    Fiber::GetThis()->yieldToMain();
}

void runSymmetricTest() {
    std::cout << "=== Running Symmetric Scheduling Test ===" << std::endl;
    sym_fibers.clear();
    // 创建 Fiber 实例，每个 Fiber 执行 symmetricFiberFunc，传入对应 id
    for (int i = 0; i < NUM_FIBERS; ++i) {
        sym_fibers.push_back(std::make_shared<Fiber>([i](){
            symmetricFiberFunc(i);
        }));
    }
    // 在主调度器中保存主上下文（使用 sylar::g_main_ctx）
    getcontext(&sylar::g_main_ctx);
    // 由主启动第 0 个 Fiber
    sym_fibers[0]->resume();
    std::cout << "=== Symmetric Test Completed ===" << std::endl;
}

// -------------------------------
// 非对称调度测试（每次 Fiber 执行后主动退回主，由主统一恢复）
// -------------------------------
std::vector<Fiber::ptr> asym_fibers;

void asymmetricFiberFunc(int id) {
    for (int i = 0; i < ITERATIONS; ++i) {
        std::cout << "[Asymmetric Fiber " << id << "] iteration " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        // 退回主上下文
        Fiber::GetThis()->yieldToMain();
    }
    std::cout << "[Asymmetric Fiber " << id << "] completed" << std::endl;
    Fiber::GetThis()->yieldToMain();
}

void runAsymmetricTest() {
    std::cout << "\n=== Running Asymmetric Scheduling Test ===" << std::endl;
    asym_fibers.clear();
    for (int i = 0; i < NUM_FIBERS; ++i) {
        asym_fibers.push_back(std::make_shared<Fiber>([i](){
            asymmetricFiberFunc(i);
        }));
    }
    // 在主调度器中保存主上下文（使用 sylar::g_main_ctx）
    getcontext(&sylar::g_main_ctx);
    bool allFinished = false;
    // 主调度器循环恢复各 Fiber
    while (!allFinished) {
        allFinished = true;
        for (int i = 0; i < NUM_FIBERS; ++i) {
            if (!asym_fibers[i]->isFinished()) {
                allFinished = false;
                std::cout << "Main: Resuming Asymmetric Fiber " << i << std::endl;
                asym_fibers[i]->resume();
            }
        }
    }
    std::cout << "=== Asymmetric Test Completed ===" << std::endl;
}

int main() {
    // 执行对称调度测试：Fiber 间直接切换
    runSymmetricTest();
    // 执行非对称调度测试：每次 Fiber 执行后退回主，由主统一恢复
    runAsymmetricTest();
    
    std::cout << "\nMain: All tests completed." << std::endl;
    return 0;
}
