#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+100 , mod = 1e9+7;
LL n ,  k ,T  ;
string s ;
LL a[2024];
void AC() {
    cin >> n ; 
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i] ;
    }
    LL ans = 1e18;
    sort(a+1,a+1+n) ;
    if ( n & 1) {
        for (int i = 1 ; i <= n; i ++) {
            LL tmp = 1 ; 
            for (int j = 1 ; j <= n ; j++) {
                if (j == i) {
                    continue;
                }
                // if (i == 3) {
                //     cout << "tm p =" <<  a[j+1] - a[j] << '\n';
                // }
                tmp = max( tmp , a[j+1] - a[j]) ;
                j++;
            }
            ans = min(ans,tmp);
        }
    } else {
        ans = 1;
        for (int i = 1 ; i <= n; i +=2) {
            ans = max( ans, a[i+1] - a[i]) ;
        }
    }
    if (n == 1) ans = 1;
    cout << ans << '\n';
}
// 0010101120011
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
0110101
01020102
0000021111
1012121010
0100202010


3
4
0
6
0



 */