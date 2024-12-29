#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+10;
#define int long long
int a[MAXN],b[MAXN],T,n,m;
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];
    sort(a+1,a+n+1),sort(b+1,b+m+1);
    int now(0),cnt(0);
    for(int i=1;i<=n;i++){
        if(a[i]==1) cnt = 1;
        else cnt++;
        a[i]--;
    }
    int i = 1,j = 1;
    a[n+1] = 1e18,b[m+1] = 1e18;
    while(1){
        if(j>m){
            printf("Yes\n");
            return;
        }
        if(a[i]<=now){
            now++;
            i++;
            continue;
        }
        else if(b[j]<=now){
            now++;
            j++;
            continue;
        }
        else{
            cnt-=(b[j]-now);
            if(cnt<0){
                printf("No\n");
                return;
            }
            j++;
            now++;
        }
    }
}
signed main(){
    cin>>T;
    while(T--) solve();
}