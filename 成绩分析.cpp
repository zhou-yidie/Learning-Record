#include <iostream>
using namespace std;
int main()
{
  int a[10010];
  int n;
  float sum = 0.0;
  int max = 0, min = 100;
  cin >> n;
  for(int i = 0; i < n; i++)
  {
    cin >> a[i];
    sum += a[i];
    if(a[i] > max)
    {
      max = a[i];
    }
    if(a[i] < min)
    {
      min = a[i];
    }
  }
  cout << max << endl << min << endl;
  printf("%.2f",(sum/n));

  // 请在此输入您的代码
  return 0;
}
