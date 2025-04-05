#ifndef SYLAR_FIBER_H
#define SYLAR_FIBER_H

#include <ucontext.h>
#include <functional>
#include <memory>
#include <thread>

namespace sylar {

// 声明为extern，仅在fiber.cpp定义
extern thread_local ucontext_t g_main_ctx;

class Fiber : public std::enable_shared_from_this<Fiber> {
public:
    using ptr = std::shared_ptr<Fiber>;
    using FiberFunc = std::function<void()>;

    Fiber(FiberFunc func, int fiber_id = -1)
        : m_cb(func)
        , m_finished(false)
        , m_fiber_id(fiber_id)
    {
        m_stack = new char[1024 * 64];
        getcontext(&m_ctx);
        m_ctx.uc_stack.ss_sp = m_stack;
        m_ctx.uc_stack.ss_size = 1024 * 64;
        m_ctx.uc_link = &g_main_ctx; // 通过uc_link传递上下文
        
        // 修正：MainFunc无参数，通过线程局部变量获取this
        makecontext(&m_ctx, &Fiber::MainFunc, 0); 
    }

    ~Fiber() {
        delete[] m_stack;
    }

    void resume();
    void yieldTo(Fiber* target);
    void yieldToMain();

    bool isFinished() const { return m_finished; }
    static Fiber* GetThis() { return t_fiber; }
    int getFiberId() const { return m_fiber_id; }

private:
    static void MainFunc(); // 无参数版本
    static thread_local Fiber* t_fiber;

    ucontext_t m_ctx;
    char*      m_stack = nullptr;
    FiberFunc  m_cb;
    bool       m_finished = false;
    int        m_fiber_id = -1;
};

} // namespace sylar

#endif
