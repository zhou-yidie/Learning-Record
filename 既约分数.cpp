#include <iostream>
using namespace std;

//欧几里得算法求最大公约数
int gcd(int a,int b)
{
  if(a<b)
  {
    swap(a,b);
  }
  if(a%b == 0)
  {
    return b;
  }
  return gcd(b,a%b);
}

int main()
{
  int a,b,i = 0;
  for(a=1;a<=2020;a++)
  {
    for(b=1;b<=2020;b++)
    {
      if(gcd(a,b) == 1)
      {
        i++;
      }
    }
  }

  cout<<i<<endl;

  return 0;
}
