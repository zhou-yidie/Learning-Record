#ifndef SYLAR_FIBER_H
#define SYLAR_FIBER_H

#include <ucontext.h>
#include <functional>
#include <memory>

namespace sylar {

// 声明全局主上下文变量，供 main.cpp 使用
extern ucontext_t g_main_ctx;

class Fiber : public std::enable_shared_from_this<Fiber> {
public:
    using ptr = std::shared_ptr<Fiber>;
    using FiberFunc = std::function<void()>;

    Fiber(FiberFunc func);
    ~Fiber();

    // 从当前上下文切换到当前 Fiber
    void resume();
    // 让当前 Fiber 将控制权直接切换到 target Fiber
    void yieldTo(Fiber* target);
    // 让当前 Fiber 将控制权退回给主上下文
    void yieldToMain();

    bool isFinished() const { return m_finished; }

    // 获取当前正在运行的 Fiber（线程局部变量）
    static Fiber* GetThis();

private:
    // Fiber 入口函数，调用用户回调函数，结束后退回主上下文
    static void MainFunc();

private:
    ucontext_t m_ctx;   // Fiber 上下文
    char*      m_stack; // 独立栈空间
    FiberFunc  m_cb;    // Fiber 回调函数
    bool       m_finished; // 是否执行完毕
};

} // namespace sylar

#endif // SYLAR_FIBER_H
