#include <ucontext.h>
#include <iostream>
#include <cstdlib>

constexpr int STACK_SIZE = 64 * 1024; // 64KB 栈空间

struct Coroutine {
    ucontext_t context;
    char* stack;
    void (*func)(Coroutine*);
    int id;
    bool finished;
    Coroutine* other; // 指向另一个协程
};

ucontext_t main_context;
Coroutine* current = nullptr;

// 协程切换函数
void yield(Coroutine* target) {
    Coroutine* prev = current;
    current = target;
    swapcontext(&prev->context, &target->context);
}

// 协程入口函数
static void coroutine_entry(Coroutine* self) {
    self->func(self);      // 执行用户定义的协程函数
    self->finished = true; // 标记协程执行完成
}

// 初始化协程
void create_coroutine(Coroutine* co, void (*func)(Coroutine*), 
                      int id, Coroutine* other) {
    co->stack = new char[STACK_SIZE];
    getcontext(&co->context);
    co->context.uc_stack.ss_sp = co->stack;
    co->context.uc_stack.ss_size = STACK_SIZE;
    co->context.uc_link = &main_context; // 执行完后返回主上下文
    makecontext(&co->context, (void(*)())coroutine_entry, 1, co);
    co->func = func;
    co->id = id;
    co->finished = false;
    co->other = other;
}

// 示例协程函数
void coroutine_func(Coroutine* self) {
    for (int i = 0; i < 3; ++i) {
        std::cout << "Coroutine " << self->id 
                  << " running (" << i + 1 << ")\n";
        yield(self->other); // 切换到另一个协程
    }
}

int main() {
    Coroutine co1, co2;
    
    // 创建两个互相指向的协程
    create_coroutine(&co1, coroutine_func, 1, &co2);
    create_coroutine(&co2, coroutine_func, 2, &co1);

    // 保存主上下文
    getcontext(&main_context);

    if (!current) {
        current = &co1; // 启动第一个协程
        swapcontext(&main_context, &co1.context);
    }

    // 当所有协程执行完毕返回主上下文
    std::cout << "All coroutines completed.\n";
    
    // 清理资源
    delete[] co1.stack;
    delete[] co2.stack;

    return 0;
}
