#include <iostream>
using namespace std;
#include <algorithm>
int n,m,t;
struct dingdan{
  int id;
  int ts;
}d[100010];
int ans = 0;
bool cmp(dingdan &a, dingdan &b){
  if(a.id == b.id){
    return a.ts < b.ts;
  }else{
    return a.id < b.id;
  }
}
bool vis[100010];
int main()
{
  cin >> n >> m >> t;
  for(int i = 1; i <= m; ++i){
    int ts,id;
    cin >> ts >> id;
    d[i] = {id,ts};
  }
  sort(d + 1,d+m+1,cmp);
  int tempid = -1;
  int sum = 0;
  bool flag = false; //记录是否之前被放入
  for(int i = 1; i <= m ;++i){
    if(tempid != d[i].id)
    {
      int ta;
      ta = t - d[i-1].ts;
      sum -= ta;
      if(sum > 3 && flag == true)
      {
        ans++;
      }
      tempid = d[i].id;
      sum = 0;
      flag = false;
      i--;
    }else{
      int ta = d[i].ts - d[i-1].ts - 1;
      if(ta > 0){
        sum -= ta;
      }
      if(sum <= 3){
        flag = false;
      }
      if(sum < 0){
        sum = 0;
      }
      sum += 2;
      if(sum > 5){
        flag = true;
      }
    }
  }
  int ta = t - d[m].ts;
  sum -= ta;
  if(sum > 5){
    ans++;
  }
  cout << ans;
  return 0;
}
