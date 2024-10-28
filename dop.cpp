#include<bits/stdc++.h>
using namespace  std ;
typedef long long LL ;
typedef pair<int,int> pii ;
#define endl '\n';
const int N = 1e4+10 ;
const int mod = 1e9+7;
int a[N];
int dp[N][N];
void AC(){
    int n , q , l , r ;
    cin >> n ;

    for (int i = 1 ; i <= n ;i ++) {
        cin >> a[i];

    }
    for (int i = 1; i <= n ; i++ ) {
        for (int j = i+1; j <= n ;j++) {
            dp[i][j] = abs(a[i] - a[j]);
        }
    }

    for (int len = 3; len <= n ; len++) {
        for (int rr = len; rr <= n; rr++) {
            int pl = rr - len + 1;
            dp[pl][rr] = min(dp[pl][rr], min(dp[pl][rr-1], dp[pl+1][rr]));
        }
    }

    cin >> q ;
    while (q--) {
        cin >> l >> r ;
        cout << dp[l][r] << '\n';
    }
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tt = 1 ;
    //cin >> tt ;
    while( tt-- ) {
        AC();
    }
}

//  1  2  3 4 5 6 7 ....n
