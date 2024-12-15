#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
 
int n;
int x;
 
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
 
	scanf("%d",&n);
	int sum=1,cnt=1,choice=0;
	bool flag=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x==1)sum++,cnt++;
		else if(x==-1)
		{
			if(cnt>1)cnt--;
			else if(choice>=1)choice--,sum++,cnt++;
			else flag=1;
		}
		else
		{
			if(cnt>1)cnt--,choice++;
			else sum++,cnt++;
		}
	}
	if(flag)printf("-1\n");
	else
	{
		cout<<sum/__gcd(sum,cnt)<<" "<<cnt/__gcd(sum,cnt)<<endl;
	}
	}
	return 0;
}
