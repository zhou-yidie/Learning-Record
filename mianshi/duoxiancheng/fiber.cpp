#include "fiber.h"
#include <iostream>
#include <cassert>

namespace sylar {

// 唯一定义（移除重复声明）
thread_local ucontext_t g_main_ctx;
thread_local Fiber* Fiber::t_fiber = nullptr;

void Fiber::resume() {
    Fiber* prev = t_fiber;
    t_fiber = this;

    std::cout << "[" << std::this_thread::get_id() << "] "
              << "Fiber(" << m_fiber_id << ") resume from "
              << (prev ? std::to_string(prev->m_fiber_id) : "main")
              << std::endl;

    if (prev) {
        swapcontext(&prev->m_ctx, &m_ctx);
    } else {
        if (g_main_ctx.uc_stack.ss_sp == nullptr) {
            getcontext(&g_main_ctx); // 首次初始化主上下文
        }
        swapcontext(&g_main_ctx, &m_ctx);
    }
}

void Fiber::yieldTo(Fiber* target) {
    Fiber* curr = t_fiber;
    t_fiber = target;

    std::cout << "[" << std::this_thread::get_id() << "] "
              << "Fiber(" << curr->m_fiber_id << ") yieldTo "
              << "Fiber(" << target->m_fiber_id << ")"
              << std::endl;

    swapcontext(&curr->m_ctx, &target->m_ctx);
}

void Fiber::yieldToMain() {
    Fiber* self = t_fiber;
    t_fiber = nullptr;

    std::cout << "[" << std::this_thread::get_id() << "] "
              << "Fiber(" << self->m_fiber_id << ") yieldTo main"
              << std::endl;

    swapcontext(&self->m_ctx, &g_main_ctx);
}

// 修正：无参数，通过t_fiber获取当前协程
void Fiber::MainFunc() {
    Fiber* self = t_fiber; // 从线程局部变量获取
    assert(self);
    if (self->m_cb) {
        self->m_cb();
    }
    self->m_finished = true;
    self->yieldToMain();
}

} // namespace sylar
