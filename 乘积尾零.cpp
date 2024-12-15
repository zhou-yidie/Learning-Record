#include <iostream>
using namespace std;

int cnt2, cnt5;


int main()
{
  for(int i = 1; i <= 10; i++)
  {
    for(int j = 1; j <= 10; j++)
    {
      int x; 
      cin >> x;
      while(x % 2 == 0)
      {
        cnt2++;
        x/=2;
      }
      while(x % 5 == 0)
      {
        cnt5++;
        x/=5;
      }
    }
  }
  cout << min(cnt2,cnt5);
  // 请在此输入您的代码
  return 0;
}
