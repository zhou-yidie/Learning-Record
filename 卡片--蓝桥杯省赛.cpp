#include<iostream>
using namespace std;

int main()
{
  int n;
  cin >> n;
  int sum = 0;
  int i;
  for(i = 1; ;i++)
  {
    sum = sum + i;
    if(sum >= n)
    {
      break;
    }
  }
  cout << i;

  system("pause");
  return 0;
}

//题目链接:https://www.lanqiao.cn/problems/2383/learning/?contest_id=80
