#include <iostream>
using namespace std;

bool isprime(int n)
{
  for(int i = 2; i * i <= n; i++)
  {
    if(n % i == 0)
    {
      return false;
    }
  }
  return true;
}

int main()
{
  int ans = 0;
  if(isprime(1949))
  {
    ans++;
  }
  if(isprime(1499))
  {
    ans++;
  }
  if(isprime(1994))
  {
    ans++;
  }
  if(isprime(4199))
  {
    ans++;
  }
  if(isprime(4919))
  {
    ans++;
  }
  if(isprime(4991))
  {
    ans++;
  }
  if(isprime(9149))
  {
    ans++;
  }
  if(isprime(9194))
  {
    ans++;
  }
  if(isprime(9419))
  {
    ans++;
  }
  if(isprime(9491))
  {
    ans++;
  }
  if(isprime(9941))
  {
    ans++;
  }
  if(isprime(9914))
  {
    ans++;
  }
  cout << ans << endl;
  // 请在此输入您的代码
  return 0;
}

************************************************************************************************************


#include <bits/stdc++.h>
using namespace std;
bool check(int x){
  for(int i=2;i<=x-1;i++){
    if(x%i==0)  return false;
  }
  return true;
}
int main()
{
  int cnt=0;
  string s="1949";
  sort(s.begin(),s.end());
  do{
    int x=stoi(s);
    if(check(x)) cnt++;
  }while(next_permutation(s.begin(),s.end()));
  cout<<cnt;
  return 0;
}

//https://www.lanqiao.cn/problems/722/learning/?page=9&first_category_id=1&sort=students_count&tags=%E7%9C%81%E8%B5%9B
