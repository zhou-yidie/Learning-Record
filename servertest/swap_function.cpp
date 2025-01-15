#include <iostream>
#include <functional>

void func0() {
    std::cout << "func0" << std::endl;
}

void func1() {
    std::cout << "func1"  << std::endl;
}

int main() {
    std::function<void()> fa = func0;
    std::function<void()> fb = func1;

    std::cout << "====交换前====" << std::endl;
    fa();
    std::cout << "fa address: " << &fa << std::endl;
    fb();
    std::cout << "fb address: " << &fb << std::endl;

    //开始交换
    fa.swap(fb);

    std::cout << "====交换后====" << std::endl;
    fa();
    std::cout << "fa address: " << &fa << std::endl;
    fb();
    std::cout << "fb address: " << &fb << std::endl;

    return 0;
}