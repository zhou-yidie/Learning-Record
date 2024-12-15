#include<bits/stdc++.h>
#define LL long long

using namespace std;
const int N=2e5+100;
LL n,h;
LL a[N] , c[N];


void solve(){
    cin >> h >> n;
    LL ans = 0 ;
    for (int i = 1; i <= n ; i++ ) cin >> a[i] ;

    for (int i = 1; i <= n ; i++ ) cin >> c[i] ;
    LL l = 1 , r = 1e12 ;
    while (l <= r) {
        LL mid = (l+r)>> 1;
        LL tp = 0;
        //cout << " l = " << l << " r = " << r << " mid = " << mid << '\n';
        for (int i = 1 ; i <= n ; i++ ) {
            tp += ((mid-1)/c[i] + 1) * a[i] ;
            if (tp >= h) {
                break ;
            }
        }
        if (tp >= h) {
            ans = mid ;
            r = mid - 1 ;
        } else {
            l = mid + 1 ;
        }
    }
    cout << ans << '\n';
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
/*

1
0
1
1
2
6
2
3
1
1



 */
