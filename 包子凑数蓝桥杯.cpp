#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5;  // 限制一个上限，只要前面能凑出来，后面都能凑出来
bool dp[MAX];  // 表示是否能凑出包子数为i的情况
int baozi[105], ans;



int main()
{
  // dp[i][j]
  int N;
  cin >> N;
  int g;
  for(int i = 1; i <= N; i++)
  {
    cin >> baozi[i];
    if(i == 1)  g = baozi[i];
    else  g = __gcd(g, baozi[i]);  // 求包子两两最大公约数
  }
  if(g != 1)  // 不互质，就会有无限个凑不出的情况
  {
    cout << "INF" << endl;
    return 0;
  }
  dp[0] = 1; // 初始化
  for(int i = 1; i <= N; i++) // 从第一种蒸笼开始
    for(int j = baozi[i]; j <= MAX; j++)  // 遍历第i种蒸笼~上限的包子数，找每个数是否能凑出来
      dp[j] = dp[j] | dp[j - baozi[i]];  // 已经凑出来 或 j-第i种包子数可以凑出来
  
  for(int i = 1; i <= MAX; i++)  // 计数凑不出来的情况
    if(!dp[i])  ans++;
  
  cout << ans;

  return 0;
}
//https://www.lanqiao.cn/problems/98/learning/?first_category_id=1&sort=students_count&second_category_id=3&tag_category_id=8
