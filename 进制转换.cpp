#include<bits/stdc++.h>
#include<iostream>
#include<string>
using namespace std;
int a[10000010];
int k;
int sum = 0;
int h, j = 0;
int m, n;
string num;
int main()
{
	
	
	cin >> m >>num >> n;
	int N = num.size();
	for (int i = 0; i < num.size(); i++)
	{
		if (num[i] < 'A')
		{
			h = pow(m, N - i - 1);
			h *= (num[i] - '0');
			sum += h;
		}
		else
		{
			h = pow(m, N - i - 1);
			h *= (num[i] - 'A' + 10);
			sum += h;
		}
	}
	while (sum > 0)
	{
		a[j++] = sum % n;
		sum /= n;
	}
	for (k = j - 1; k >= 0; k--)
	{
		if (a[k] >= 10)
			cout << (a[k] + 'A' - 10);
		else
			cout << a[k];
	}

	return 0;
}
