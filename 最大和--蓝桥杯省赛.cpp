#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;
typedef long long ll;
const int N = 1e4;
int a[N];
vector<long long >dp(N,LONG_MIN);
int n;
int getNum(int num)//求解最小质因子 
{
    if(num == 1)return 1;
    if(num%2 == 0)return 2;
    for(int i = 3; i <= sqrt(num); i+=2)
    {
        if(num%i == 0)return i;
    }
    return num;
}
int main()
{    
cin>>n;
for(int i = 1; i <= n; i++)
{
    cin>>a[i];
}
dp[1] = a[1];
dp[2] = dp[1] + a[2];
for(int i = 1; i < n; i++)
{
    int k = i + getNum(n - i);
    for(int j = i + 1; j <= k&&j <= n; j++)
    {
    if(j > 2)
    dp[j] = max(dp[j],dp[i] + a[j]);
    }
}
cout<<dp[n]<<endl;
    return 0;
}

//https://www.lanqiao.cn/problems/2385/learning/?contest_id=80
