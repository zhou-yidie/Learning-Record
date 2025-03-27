#include "fiber.h"
#include <assert.h>
#include <iostream>

namespace sylar {

// 定义全局主上下文变量
ucontext_t g_main_ctx;

// 线程局部变量，保存当前运行的 Fiber
static thread_local Fiber* t_fiber = nullptr;

Fiber::Fiber(FiberFunc func)
    : m_cb(func)
    , m_finished(false)
{
    // 分配独立栈（可根据需要调整大小）
    m_stack = new char[1024 * 64];
    getcontext(&m_ctx);
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = 1024 * 64;
    // 对称调度下 uc_link 设为 nullptr，由 Fiber 内部主动切换回主上下文
    m_ctx.uc_link = nullptr;
    // 设置入口函数为 MainFunc
    makecontext(&m_ctx, MainFunc, 0);
}

Fiber::~Fiber() {
    delete[] m_stack;
}

void Fiber::resume() {
    Fiber* prev = t_fiber;
    t_fiber = this;
    if (prev) {
        // 当前在某个 Fiber 内，从 prev 切换到当前 Fiber
        swapcontext(&prev->m_ctx, &m_ctx);
    } else {
        // 从主上下文切换到当前 Fiber
        swapcontext(&g_main_ctx, &m_ctx);
    }
}

void Fiber::yieldTo(Fiber* target) {
    Fiber* prev = t_fiber;
    t_fiber = target;
    swapcontext(&prev->m_ctx, &target->m_ctx);
}

void Fiber::yieldToMain() {
    Fiber* self = t_fiber;
    t_fiber = nullptr;
    swapcontext(&self->m_ctx, &g_main_ctx);
}

Fiber* Fiber::GetThis() {
    return t_fiber;
}

void Fiber::MainFunc() {
    Fiber* cur = t_fiber;
    if(cur && cur->m_cb) {
        cur->m_cb();
    }
    cur->m_finished = true;
    t_fiber = nullptr;
    // 执行完毕后，退回到主上下文
    setcontext(&g_main_ctx);
    // 不应返回到此处
    assert(false);
}

} // namespace sylar
