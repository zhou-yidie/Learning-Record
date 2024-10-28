#include<iostream>

using namespace std;
int n;
int prime[1000] = { 0 };

void test()   //线性筛选质数
{
	for (int i = 2; i * 2 <= 100; i++)
	{
		if (prime[i] == 0)
		{
			for (int j = 2 * i; j <= 100; j += i)
			{
				prime[j] = 1;
			}
		}
	}
}

int main()
{
	//cin >> n;
	n = 100;
	test();

	for (int i = 2; i <= 100; i++)
	{
		if (prime[i] == 0)
			cout << i << endl;
	}


	return 0;
}
