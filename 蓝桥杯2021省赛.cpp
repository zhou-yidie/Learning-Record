#include <iostream>
using namespace std;
int main()
{
  // 请在此输入您的代码
  int n;
  int sum=0;
  cin>>n;
  for(int i=1;i<=n-1;i++) {
    if((i*i)%n<n/2.0) sum++;
  }
  cout<<sum<<endl;
  return 0;
}
