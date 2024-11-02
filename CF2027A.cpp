#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , q ,ans ;

bool mp[110][110];

void AC() {
    memset(mp , false , sizeof(mp));
    cin >> n ; ans =0 ;
    LL mx_m = 0 , mx_q = 0 ;
    for (int i = 1; i <= n ; i++) {
        cin >> m >> q ;
        mx_m = max(m, mx_m); mx_q = max(q , mx_q);
        for (int j = 1 ; j <= m ; j++) {
            for (int k = 1 ;  k<= q ; k++) {
                mp[j][k] = true ;
            }
        }
    }
    for (int i = 1 ; i <= mx_m ; i++) {
        for (int j = 1 ; j <= mx_q ;j++) {
            if (!mp[i][j]) continue ;
            if (!mp[i-1][j]) ans++;
            if (!mp[i+1][j]) ans++;
            if (!mp[i][j-1]) ans++;
            if (!mp[i][j+1]) ans++;
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