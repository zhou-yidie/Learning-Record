#include<iostream>
#include<algorithm>
using namespace std;
long long x[1000010] = { 0 }, y[1000010] = { 0 };
int h = 0, l = 0;
int n, k;

int main()
{
	cin >> n >> k;
	for (int i = 0; i < k; i++)
	{
		cin >> x[i] >> y[i];
	}
	sort(x, x + k);
	sort(y, y + k);
	for (int j = 0; j < k; j++)
	{
		if (x[j] != x[j + 1])
			h++;
		if (y[j] != y[j + 1])
			l++;
	}
	h = n - h;
	l = n - l;
	cout << (n * n - h * l);
	return 0;
}
