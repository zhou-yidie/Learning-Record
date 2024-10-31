#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 1e3+50 , mod = 1e9+7;

LL n , k , a[N] , b[N] , c[N] , d[N] , dp[N][N*4];

void AC() {
    cin >> n >> k ;
    for (int i = 1 ; i  <= n + 3 ;i ++ ) {
        for (int j = 1 ; j <= k+5 ; j ++ ) {
            dp[i][j] = 1e15;
        }
    }
    for (int i = 1; i <= n ; i++ ) cin >> a[i] >> b[i] >> c[i] >> d[i];
    dp[1][1] = a[1] , dp[1][2] = b[1] , dp[1][3] = c[1] , dp[1][4] = d[1] ,dp[1][0] = 0;
    for (int i = 2 ; i <= n ; i++) {
        for (int j = 0; j <= k ; j++) {
            dp[i][j] = min(dp[i][j] , dp[i-1][j] );
            if (j >= 1) dp[i][j] = min(dp[i][j] , dp[i-1][j-1] + a[i] ) ;
            if (j >= 2) dp[i][j] = min(dp[i][j] , dp[i-1][j-2] + b[i] ) ;
            if (j >= 3) dp[i][j] = min(dp[i][j] , dp[i-1][j-3] + c[i] ) ;
            if (j >= 4) dp[i][j] = min(dp[i][j] , dp[i-1][j-4] + d[i] ) ;
        }
        
    }
    LL ans = LONG_LONG_MAX;
    for (int i = 1 ; i <= n ; i++ ) {
        ans = min(ans , dp[i][k]);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}