#include <iostream>
using namespace std;

bool yes(int num)
{
  while(num > 0）
  {
    if(num % 10 == 2 || num % 10 == 0 || num % 10 == 1 || num % 10 == 9) return true;
    num /= 10;
  }
  return false;
}

int main()
{
  // 请在此输入您的代码
  int sum = 0;
  for(int i = 1; i <= 2019; ++i)
  {
    if(yes(i)) sum += i;
  }
  cout << sum;
  return 0;
}
