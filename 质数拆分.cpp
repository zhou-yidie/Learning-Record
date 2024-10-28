#include <iostream>
using namespace std;
int isprime(int n){
  for(int i=2;i*i<=n;i++){
    if(n%i==0){
      return 0;
    }
  }
  return 1;
}
int main()
{
  int prime[2000];
  int cnt=1;//这里从下标1开始计，方便后面dp使用
  for(int i=2;i<=2019;i++){
    if(isprime(i)){
      prime[cnt++]=i;
    }
  }
  long long dp[2500][2500];
  //dp[i][j]前i个数 组成j大小的数的方法数
  //总共有两个状态

  //1、初始化
  dp[0][0]=1;
  for(int i=1;i<=2019;i++){
    dp[0][i]=0;//一个数都不选的时候，只能组成0，其他数不能组成
  }

  for(int i=1;i<cnt;i++){
    for(int j=0;j<=2019;j++){
      dp[i][j]=dp[i-1][j];
      if(prime[i]<=j){
        dp[i][j]=dp[i][j]+dp[i-1][j-prime[i]];
      }
    }
  }
  cout<<dp[cnt-1][2019];
  return 0;
}
