#include<bits/stdc++.h>
#define LL long long

using namespace std;
const int N=(int)1e6+100 , mod = 998244353;
LL n,h;
LL a[N] ,s[N] , pw[N << 1];
LL ans , cnt , mn ;

void solve(){
    cin  >> n;
    for (int i = 1 ; i <= n ; i++ ) { cin >> a[ i ] ; }
    ans = cnt = 0 ; mn = a[1];
    for (int i = 1 ; i <= n ; i++ ) {
        s[i] = s[i-1] + a[i] ; mn = min(mn,s[i]) ;
    }
    for (int i = 1; i <= n ;i++ ) {
        if (s[i] >= 0) cnt++;
        if (s[i] == mn && mn < 0 ) ans = (ans + pw[cnt+n-i]) % mod ;
    }
    if (mn >= 0) ans = pw[n];
    cout << ans << '\n';
    return ;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int T=1; pw[0] = 1;
    for (int i = 1; i <= 2e6 ; i++ ) {
        pw[i] = (pw[i-1] << 1) % mod ;
    }
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
