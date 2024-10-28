#include<bits/stdc++.h>
#define LL long long

using namespace std;
const int N=5e5+100;
LL n,k,sm ,ans;

LL dp[1010];
void solve(){
    cin >> n >> k ;
    ans = 0 ;
    if (n == 1 ) {
        cout << "0\n" ;
        return ;
    }
    cout << (n-1 + k-2 )/(k-1) << '\n';
//    for (int i = 1 ; i <= n ; i++ ) {
//        dp[i] = N ;
//    }
//    dp[0] = 0 ;
//    for (int i = 2 ; i <= k ; i++ ) {
//        dp[i] = 1 ;
//    }
//    dp[1] = 0 ;
//    for (int i = k+1 ; i <= n ; i++ ) {
//        for (int j = i - 1 ; j >= 1 ; j-- ) {
//            LL ct = (i+j-1) / j ;
//            LL cnt = min(ct-1 , k-1) ;
//            dp[i] = min(dp[i] , cnt*(dp[j]) + dp[ i - cnt * j ] + 1) ;
//        }
//    }
//    for (int i = 1;  i<= n ; i++ ) {
//        cout <<  i <<  "  " << dp[i] << '\n';
//    }
//    cout << dp[n] << endl;
    return ;
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
