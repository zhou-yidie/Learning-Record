#include<iostream>
using namespace std;

//class person
//{
//	friend ostream& operator<<(ostream& cout, person& p);
//public:
//	person(int a, int b)
//	{
//		this->m_A = a;
//		this->m_B = b;
//	}
//private:
//	int m_A;
//	int m_B;
//};

//ostream& operator<<(ostream& cout, person& p)
//{
//	cout << "a= " << p.m_A << " b=" << p.m_B;
//	return cout;
//}

class myinter
{
	friend ostream& operator<<(ostream& cout, myinter myint);
public:
	myinter()
	{
		n_num = 0;
	}

	myinter& operator--()
	{
		n_num--;
		return *this;
	}
	myinter operator--(int)
	{
		myinter temp = *this;
		n_num--;
		return temp;
	}
private:
	int n_num;
};


ostream& operator<<(ostream& cout, myinter myint)
{
	cout << myint.n_num;
	return cout;
}

void test01()
{
	myinter myint;
	cout << --myint << endl;
	cout <<endl << myint << endl << endl;
}

void test02()
{
	myinter myint;
	cout << myint-- << endl;
	cout << myint << endl;
}

int main()
{
	/*person p1(10, 30);

	cout << p1 << endl;*/
	test01();

	test02();

	system("pause");

	return 0;
}