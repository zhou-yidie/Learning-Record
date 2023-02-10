#include<bits/stdc++.h>
using namespace std;


bool zhishu(int x)
{
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
			return false;
	}
	return true;
}

void put(int n)
{
	cout << n << '=';
	int i;
	for (i = 2; i < n; i++)
	{
		if (zhishu(i) && zhishu(n - i))
		{
			cout << i << '+' << (n - i) << endl;
			break;
		}
	}
}

int main()
{
	int i, n;
	cin >> n;
	for (i = 4; i <= n; i += 2)
	{
		put(i);
	}


	return 0;
}
