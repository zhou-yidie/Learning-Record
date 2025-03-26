// #include <iostream>
// using namespace std;

// template <typename T>
// class Unique_ptr {
// private:
//     T* ptr_;
//     // 禁用拷贝构造函数和重载＝,从而独占对象
//     Unique_ptr(Unique_ptr<T> const& up) = delete;
//     Unique_ptr<T>& operator=(Unique_ptr<T> const& up) = delete;
//     void del() {
//         if (ptr_)  // 防止释放所有权后delete
//         {
//             delete ptr_;
//             ptr_ = nullptr;  // 防止野指针
//         }
//     }

// public:
//     Unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}
//     ~Unique_ptr() {
//         del();
//     }
//     T& operator*() const {
//         return *ptr_;
//     }
//     void reset() {
//         del();
//     }
//     T* get() const {
//         return ptr_;
//     }
//     T* release() {
//         T* p = ptr_;
//         ptr_ = nullptr;
//         return p;
//     }
//     T* operator->() {
//         return ptr_;
//     }
// };

// template <typename T>
// T* move(Unique_ptr<T>& tmp) {
//     if (tmp.get()) {
//         return tmp.release();
//     }
//     return nullptr; // 确保在条件不满足时返回nullptr
// }

// int main() {
//     Unique_ptr<int> up(new int(42));
//     int* rawPtr = move(up);
//     if (rawPtr) {
//         cout << "Moved value: " << *rawPtr << endl;
//         delete rawPtr;
//     }
//     return 0;
// }


// #include <iostream>
// #include <utility> // for std::move

// template<typename T>
// class UniquePtr {
// private:
//     T* ptr; // 原始指针

// public:
//     // 构造函数
//     explicit UniquePtr(T* p = nullptr) : ptr(p) {}

//     // 禁止复制构造函数
//     UniquePtr(const UniquePtr&) = delete;

//     // 禁止复制赋值操作符
//     UniquePtr& operator=(const UniquePtr&) = delete;

//     // 移动构造函数
//     UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
//         other.ptr = nullptr; // 将源指针置为空
//     }

//     // 移动赋值操作符
//     UniquePtr& operator=(UniquePtr&& other) noexcept {
//         if (this != &other) {
//             delete ptr; // 释放当前持有的资源
//             ptr = other.ptr; // 转移所有权
//             other.ptr = nullptr; // 将源指针置为空
//         }
//         return *this;
//     }

//     // 析构函数
//     ~UniquePtr() {
//         delete ptr; // 释放资源
//     }

//     // 重载 * 操作符
//     T& operator*() const {
//         return *ptr;
//     }

//     // 重载 -> 操作符
//     T* operator->() const {
//         return ptr;
//     }

//     // 获取原始指针
//     T* get() const {
//         return ptr;
//     }

//     // 释放所有权并返回原始指针
//     T* release() {
//         T* temp = ptr;
//         ptr = nullptr;
//         return temp;
//     }

//     // 重新设置指针
//     void reset(T* p = nullptr) {
//         if (ptr != p) {
//             delete ptr; // 释放当前持有的资源
//             ptr = p; // 设置新的指针
//         }
//     }
// };

// class MyClass {
// public:
//     MyClass() { std::cout << "MyClass constructed\n"; }
//     ~MyClass() { std::cout << "MyClass destroyed\n"; }
//     void sayHello() { std::cout << "Hello\n"; }
// };

// int main() {
//     UniquePtr<MyClass> ptr1(new MyClass());
//     ptr1->sayHello();

//     // UniquePtr<MyClass> ptr2 = ptr1; // 错误：不能复制 unique_ptr
//     UniquePtr<MyClass> ptr2 = std::move(ptr1); // 移动所有权

//     if (!ptr1.get()) {
//         std::cout << "ptr1 is empty\n";
//     }
//     if (ptr2.get()) {
//         ptr2->sayHello();
//     }
//     return 0;
// }


#include<iostream>
 
template<typename T>
class UniquePtr{
public:
    //定义构造函数
	explicit UniquePtr(T* ptr):ptr_(ptr){}
	//定义析构函数
    ~UniquePtr(){
		delete ptr_;
		ptr_=nullptr;
	}
    //禁止拷贝和赋值
	UniquePtr(const UniquePtr&)=delete;
	UniquePtr& operator=(const UniquePtr&)=delete;
    //允许移动构造和移动赋值
	UniquePtr(UniquePtr&& rhs) noexcept :ptr_(rhs.ptr_){
		rhs.ptr_=nullptr;
	}
	UniquePtr& operator=(UniquePtr&& rhs){
		if(this!=&rhs){
			delete ptr_;
			ptr_=rhs.ptr_;
			rhs.ptr_=nullptr;
		}
		return *this;
	}
 
	T* release()  {
		T* tmp=ptr_;
		ptr_=nullptr;
		return tmp;
	}
    //类型转换函数
	template<typename U>
	UniquePtr(UniquePtr<U>&& rhs) noexcept :ptr_(rhs.release()){}
	//重载指针操作
	T& operator*() const{
		return *ptr_;
	}
 
	T* operator->() const{
		return ptr_;
	}
    //获取裸指针
	T* get() const{
		return ptr_;
	}
 
private:
	T* ptr_;
};
 
class Base{
public:
	char* str="hello";
protected:
	int num;
};
 
class Derive:public Base{
private:
	double  num1;
};
 
void Test(){
	UniquePtr<int> sp1(new int(42));
	std::cout<<*sp1<<std::endl;
	UniquePtr<int> sp2(std::move(sp1));
	
	UniquePtr<double> sp3(new double(3.14));
	std::cout<<*(sp3)<<std::endl;
	UniquePtr<double> sp4=(std::move(sp3));
 
	UniquePtr<Base> bp1(new Base);
	std::cout<<bp1->str<<std::endl;
	UniquePtr<Derive> dp1(new Derive);
	bp1=std::move(dp1);
}
 
int main()
{
	Test();
	return 0;
}
 