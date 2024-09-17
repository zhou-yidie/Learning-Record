#include<iostream>
#include<cstdio>

using namespace std;

int n, k;
int a[25];
long long ans;


bool isprime(int x)
{
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
			return false;
	}
	return true;
}

void dfs(int num, int sum, int qi)
{
	if (num == k)
	{
		if (isprime(sum))
			ans++;
		return;
	}
	for (int i = qi; i <= n; i++)
	{
		dfs(num + 1, sum + a[i], i + 1);
	}
	return;
}





int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	dfs(0, 0, 1);
	cout << ans << endl;

	return 0;
}
