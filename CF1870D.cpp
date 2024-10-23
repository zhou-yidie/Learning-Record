#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+100 , mod = 1e9+7;
LL n ,ans[N],a[N] , k , mn ,T ;


void AC() {
    cin >> n ;
    for( int i =0 ;  i <= n+5 ; i++ ) ans[i] = 0 ;
    ans[0] = INT_MAX , mn = INT_MAX;
    for (int i =1 ; i <= n ; i++ ) { cin >> a[i] ; }
    cin >> k ;
    for (int i = n ; i >= 1 ; i-- ) mn = min( mn , a[i]) , a[i] = mn ;
    for (int i = 1 ; i <= n ; i++ ) {
        if (a[i] == a[i-1]) ans[i] = ans[i-1] ;
        else ans[i] = min(ans[i-1] , k/(a[i]-a[i-1])) ;
        k = k - (a[i] - a[i-1]) * ans[i];
        cout << ans[i] <<  " " ;
    }
    cout << '\n';
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
