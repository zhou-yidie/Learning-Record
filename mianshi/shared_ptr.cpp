#include <iostream>
#include <mutex>
using namespace std;


template <class T>
class mySharedPtr
{
private:
 
    T* _ptr;             //被封装的指针
    int* _pcount;        //当shared_ptr指向同一对象时共享的那个计数
    mutex* _pmtx;        //当shared_ptr指向同一对象时共享的锁
 
public:
 
    //构造函数
    mySharedPtr(T* ptr):_ptr(ptr),_pcount(new int(1)),_pmtx(new mutex)
    {};                                     //构造函数

    mySharedPtr(const mySharedPtr<T>& sp):_ptr(sp._ptr),_pcount(sp._pcount),_pmtx(sp._pmtx) //拷贝构造函数
    {
        addCount();            //因为和被拷贝的shared_ptr指向同一个对象，因此增加计数。
    }
                    
    
    //功能函数
    void release();                                          //解除绑定
    void addCount();                                         //增加计数
    void showCount();                                        //显示计数（非必须）
 
    //运算符重载
    mySharedPtr& operator=(const mySharedPtr<T> &sp);        //=   赋值重载
    T& operator*();                                          //*   指针解引用重载
    T* operator->();                                         //->  指针访问重载
 
    //析构函数
    ~mySharedPtr() {
        release();
    };
};

template<class T>
void mySharedPtr<T>::release(){
    _pmtx->lock();
    bool deleteflag=false;
    //锁不能在lock时delete 
    //而在lock后不一定需要delete
    //所以一个标志位告诉解锁后需不需要delete mutx
    if(--(*_pcount)==0){
        cout<<"delete:"<<*_ptr<<endl;
        delete[] _ptr;
        delete _pcount;
        deleteflag=true;
    }
    _pmtx->unlock();
    if(deleteflag == true){
        delete _pmtx;
    }
}

template<class T>
void mySharedPtr<T>::addCount(){
    _pmtx->lock();
    ++(*_pcount);
    _pmtx->unlock();
}

template<class T>
void mySharedPtr<T>::showCount(){
    cout<<(*_ptr)<<" "<<(*_pcount)<<endl;
}

template<class T>
mySharedPtr<T>& mySharedPtr<T>::operator=(const mySharedPtr<T>& sp){
    if(_ptr!=sp._ptr){//防止自我赋值
        release();
        _ptr=sp._ptr;
        _pcount=sp._pcount;
        _pmtx=sp._pmtx;
        addCount();
    }
    return *this;
}

template<class T>
T& mySharedPtr<T>::operator*(){
    return *_ptr;
}

template<class T>
T* mySharedPtr<T>::operator->(){
    return _ptr;
}

int main()
{
    mySharedPtr<char> a(new char('a'));
    a.showCount();
    
    mySharedPtr<char> b(a);
    b.showCount();
    
    mySharedPtr<char> c(new char('b'));
    c.showCount();
    
    c=b;
    c.showCount();
    
    return 0;
}