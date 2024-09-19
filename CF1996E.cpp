#include<bits/stdc++.h>
using namespace  std ;
typedef long long LL ;
typedef pair<int,int> pii ;
const int N = 2e5+10 ;
const int mod = 1e9+7;

LL n , x  ;

LL a[N] , sum[N] , ans;
map<LL , LL> mp;
char s[N];
void AC(){
    scanf("%s",s+1);n=strlen(s+1);mp.clear();ans=0;mp[0]=1;
    for(int i=1;i<=n;i++)a[i]=(s[i]=='1'?1:-1),sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++){
        ans=(ans+(n-i+1)*mp[sum[i]]%mod)%mod;mp[sum[i]]+=i+1;
    }
    printf("%lld\n",ans);
}



int main(){
//    ios::sync_with_stdio(0);
//    cin.tie(0);cout.tie(0);
    int tt = 1 ;
    cin >> tt ;
    while( tt-- ) {
        AC();
    }
}

//  1  2  3 4 5 6 7 ....n
