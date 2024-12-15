#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+100 , mod = 1e9+7;
LL n ,a[N] , k ,T , dp[N][3] ;


void AC() {
    cin >> n ;
    for (int i = 1; i <= n ; i++ ) cin >> a[i] ;
    dp[1][0] = 0 ;dp[1][1] = 1;dp[1][2] = 1;
    for (int i = 2 ; i <= n ; i++ ) {
        LL mnn = (dp[i-1][0] < dp[i-1][1]) ? ( (dp[i-1][0] < dp[i-1][2]) ? dp[i-1][0] : dp[i-1][2] ) : ( (dp[i-1][1] < dp[i-1][2]) ? dp[i-1][1] : dp[i-1][2] );
        if (a[i] == a[i-1]) {
            dp[i][0] = dp[i-1][2] ;
            dp[i][1] = 1LL + mnn;
            dp[i][2] = dp[i-1][2] + 1;
        } else if (a[i] > a[i-1]) {
            dp[i][0] = mnn ;
            dp[i][1] = min(dp[i-1][0] + 1 , dp[i-1][1] ) ;
            dp[i][2] = dp[i-1][2] + 1;
        } else {
            dp[i][0] = dp[i-1][2] ;
            dp[i][1] = 1LL + mnn ;
            dp[i][2] = dp[i-1][2] ;
        }
    }
    cout << min({dp[n][0] , dp[n][1] , dp[n][2]} ) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}

/*
5
00100
01110
11111
11111
11111
 */