#include <iostream>
using namespace std;
long long n,sum;
long long ans;
int a[200010];
int main()
{
  cin >> n;
  for(long long i = 1; i <= n; i++)
  {
    cin >> a[i];
    sum += a[i];
  }
  for(long long i = 1; i <= n; i++)
  {
    ans += a[i] * (sum -a[i]);
  }
  cout << ans/2;
  // 请在此输入您的代码
  return 0;
}
