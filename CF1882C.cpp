#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , q , k ,ans ;
LL a[N] ;
void AC() {
    cin >> n ; ans = 0 ;
    for (int i = 0; i <= N ; i ++ ) a[i] = 0 ;
    for (int i = 1; i <= n ; i++ ) {
        cin >> a[i];
        if ( i >= 3 && a[i] > 0) ans += a[i] ;
    }
    if (a[1] >= 0 && a[2] >= 0) ans += a[1] + a[2] ;
    else if (a[1] >= 0) ans += a[1] ;
    else if (a[1] + a[2] > 0) ans += a[1]+a[2] ;
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