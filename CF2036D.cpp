#include<bits/stdc++.h>
#define i64 long long
#define L(a,b,c,d) for(int a=b;a<=c;a+=d)
#define R(a,b,c,d) for(int a=b;a>=c;a-=d)

using namespace std;
const int N=1e3+5,M=998244353;

void solve();
int T,n,m,ans;
char s[N][N];

signed main(){
  scanf("%d",&T);
  while(T--) solve();
  return 0;
}

int sol(int x,int y,int i){
  int ans=0,u=x,v=y;
  vector<char> a;
  while(1){
    a.push_back(s[x][y]);
    if(a.size()==4){
      if(a[0]=='1'&&a[1]=='5'&&a[2]=='4'&&a[3]=='3') ans++;
      a.erase(a.begin());
    }
    if(x==i){
      if(y==m-i+1) x++;
      else if(y==i) y++;
      else y++;
    }
    else if(x==n-i+1){
      if(y==i) x--;
      else if(y==m-i+1) y--;
      else y--;
    }
    else if(y==m-i+1){
      if(x==n-i+1) y--;
      else if(x==i) x++;
      else x++;
    }
    else if(y==i){
      if(x==i) y++;
      else if(x==n-i+1) x--;
      else x--;
    }
    if(x==u&&y==v) break;
  }
  return ans;
}

void solve(){
  scanf("%d%d",&n,&m);
  L(i,1,n,1) scanf("%s",s[i]+1);
  ans=0;
  L(i,1,min(n,m)/2,1){
    int x=i,y=i;
    while(1){
      if(s[x][y]=='1') break;
      if(x==i){
        if(y==m-i+1) x++;
        else if(y==i) y++;
        else y++;
      }
      else if(x==n-i+1){
        if(y==i) x--;
        else if(y==m-i+1) y--;
        else y--;
      }
      else if(y==m-i+1){
        if(x==n-i+1) y--;
        else if(x==i) x++;
        else x++;
      }
      else if(y==i){
        if(x==i) y++;
        else if(x==n-i+1) x--;
        else x--;
      }
      if(x==i&&y==i) break;
    }
    ans+=sol(x,y,i);
  }
  printf("%d\n",ans);
}