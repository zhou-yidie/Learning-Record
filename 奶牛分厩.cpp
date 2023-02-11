#include<iostream>
#include<cmath>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;


int N ;
int s[1000010], a[1000010];



int main()
{
	cin >> N;
	int i;
	for (i = 1; i <= N; i++)
	{
		cin >> s[i];
	}
	for (int o = 1; o <= N; o++)
	{
		for (int j = 1; j <= N; j++)
		{
			a[abs(s[j] - s[o])] = 1;
		}
	}

	for (int i = N; ; i++)
	{
		if (a[i] == 0)
		{
			int flag = 1;
			for (int j = i + i;j < 1000010; j += i)
			{
				if (a[j])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				cout << i;
				break;
			}
		}
		
	}
	
	return 0;
}
