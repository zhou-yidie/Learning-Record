#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 3e5+50 , mod = 1e9+7;

LL n , m , q ,ans ;

LL a[N],b[N] , c[N] ;
LL s[N] , f[2][N];
void AC() {
    cin >> n >> m; ans = 0 ;
    LL a_mx = 0 ,b_mx = 0; c[n+1] = 0;
    for (int i = 1 ; i<= n ; i++ ) {
        cin >> a[i];
        a_mx = max(a_mx,a[i]);
        s[i] = s[i-1] + a[i];
    }
    for (int i = n ; i >= 1 ; i--) {
        c[i] = max(c[i+1] , a[i]);
    }
    for (int i = 1 ; i<= m ; i++ ) {
        cin >> b[i];
        b_mx = max(b_mx,b[i]);
    }

    if (a_mx > b_mx) {
        cout << "-1\n" ;
        return ;
    }
    int now = 1;
//    for (int i = 1 ; i < m ; i++ ) {
//        //if (b[i] < b[i+1]) continue ;
//        //if (d[i+1] >= b[i]) continue ;
//        if (b[i+1] >= c[pre]) continue;
//        //cout << " i = " << i << '\n';
//        LL tp = 0 , j = pre ;
//        while (j <= n && b[i+1] < c[j]) {
//            j++;
//        }
//        for (int k = pre ; k < j ; k ++) {
//            if (tp + a[k] > b[i]) {
//                ans += (m-i) ;
//                tp = a[k] ;
//            } else {
//                tp += a[k];
//            }
//        }
////        for (j = pre ; j <= n && d[i+1] < c[j] ;j ++) {
////            if (tp + a[j] > b[i]) {
////                ans += (m-i) ;
////                tp = a[j] ;
////            } else {
////                tp += a[j];
////            }
////        }
//        //cout <<
//        pre = j ;
//        cout << " pre = " << pre<< '\n';
//        if (tp != 0) {
//            ans+= (m-i);
//        }
//    }
    for (int i = 1 ; i <= n; i++) f[0][i] = 1e18 ;
    for (int i = 1; i <= m; ++ i, now ^= 1) {
        for (int r = 1, l = 1; r <= n; ++ r) {
            f[now][r] = f[now ^ 1][r];
            while (l <= r && s[r] - s[l - 1] > b[i]) ++ l;
            if (l <= r) f[now][r] = min(f[now][r], f[now][l - 1] + m - i);
        }
    }
    cout << f[now ^ 1][n] << "\n";
    //cout <<   ans << '\n';
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