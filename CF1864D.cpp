#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 3e3+10 , mod = 1e9+7;
LL n , a[N][N] , s[N][N];


void AC() {
    cin >> n ;
    for (int i = 1; i <= n ; i++ ) {
        for (int j =1 ; j <= n ; j++ ) {
            char c ; cin >> c ;
            if (c == '0') a[i][j] = 0 ;
            else a[i][j] = 1 ;
            s[i][j] = 0 ;
        }
    }
    LL ans = 0 ;
    for (int i = 1; i <= n ; i++ ) {

        for (int j =1 ; j <= n ; j++ ) {

            if (s[i][j] & 1) { a[i][j] = 1 - a[i][j] ; }

            if (a[i][j] & 1) {
                a[i][j] = 1 - a[i][j] ;
                ans+= 1;
                s[i][j] += 1 ;
            }
            if (s[i][j] & 1) {
                a[i+1][j] = 1 - a[i+1][j] ;
                s[i+1][j-1]++ ; s[i+1][j+1] ++ ;
                if (j != 1 && j != n) s[i+2][j] += s[i][j] ;
            }

        }

    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T = 1 ;
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