// sym_coroutine.hpp
#ifndef SYM_COROUTINE_HPP
#define SYM_COROUTINE_HPP

#include <ucontext.h>
#include <memory>
#include <cstdio>
#include <unistd.h>

class SymCoroutine {
public:
    using TaskFunc = void (*)(SymCoroutine*);

    // 主协程（当前线程栈）
    SymCoroutine() {
        if (getcontext(&ctx) == -1) { perror("main coro"); _exit(1); }
        state = RUNNING;
    }

    // 子协程（独立栈）
    SymCoroutine(TaskFunc func, SymCoroutine* target = nullptr, 
                 size_t stack_size = 1024*1024)
        : task(func), target(target) {
        stack = std::make_unique<char[]>(stack_size);
        
        if (getcontext(&ctx) == -1) { perror("sub coro"); _exit(1); }
        
        ctx.uc_stack.ss_sp = stack.get();
        ctx.uc_stack.ss_size = stack_size;
        ctx.uc_link = &target->ctx; // 直接绑定目标上下文
        
        // 入口函数直接接收协程指针
        makecontext(&ctx, (void(*)())entry, 1, this);
    }

    // 切换到目标协程（主协程专用）
    void resume(SymCoroutine* target) {
        swapcontext(&ctx, &target->ctx);
    }

    // 协程间切换（子协程专用）
    void jump(SymCoroutine* target) {
        swapcontext(&ctx, &target->ctx);
    }

    // 挂起（返回uc_link）
    void yield() {
        swapcontext(&ctx, ctx.uc_link);
    }

private:
    enum { READY, RUNNING, SUSPENDED, FINISHED } state = READY;
    ucontext_t ctx{};
    std::unique_ptr<char[]> stack;
    TaskFunc task = nullptr;
    SymCoroutine* target = nullptr;

    // 静态入口函数（直接接收协程指针）
    static void entry(SymCoroutine* self) {
        self->state = RUNNING;
        self->task(self); // 执行用户任务
        self->state = FINISHED;
        self->yield(); // 结束后返回目标
    }

    // 禁止拷贝
    SymCoroutine(const SymCoroutine&) = delete;
    SymCoroutine& operator=(const SymCoroutine&) = delete;
};
#endif
