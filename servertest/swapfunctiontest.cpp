#include <iostream>
#include <functional>

void print(){
    std::cout << "Hello I am XYZ" << std::endl;
}

void func(std::function<void()> cb){
    std::cout << "函数传入后的地址:" << &cb << std::endl;
    std::cout << "传入函数后调用" << std::endl;
    cb();
}


int main(int argc, char** argv){
    std::function<void()> f = print;
    std::cout << "函数传入前的地址:" << &f << std::endl;
    func(f);
    std::cout << "回调完成后再次调用" << std::endl;
    f();
    return 0;
}
