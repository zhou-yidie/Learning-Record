#include <iostream>
class MyClass {
public:
    // 使用 explicit 关键字修饰单参数构造函数
    explicit MyClass(int value) : data(value) {}
    void printData() {
        std::cout << "Data: " << data << std::endl;
    }
private:
    int data;
};

void func(MyClass obj) {
    obj.printData();
}

int main() {
    // 显式类型转换
    func(MyClass(10));
    // 下面这行代码会导致编译错误，因为禁止了隐式类型转换
    func(10);
    return 0;
}