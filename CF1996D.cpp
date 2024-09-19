#include<bits/stdc++.h>
using namespace  std ;
typedef long long LL ;
typedef pair<int,int> pii ;
const int N = 2e5+10 ;
const int mod = 1e9+7;

LL n , x  ;

void AC(){
    cin >> n >> x ;
    LL mx = max( n , x ) ;
    LL ans = 0 ;
    for (int i = 1 ; i <= mx ; i++ ) {
        for (int j = 1 ; j <= (mx + i-1) / i ; j ++ ) {
            LL l = 0 , r = x - i - j ;
            if (r <= l) continue ;
            LL add = i * j , mul = (i+j);
            while (l < r) {
                LL mid = (l+r+1) >> 1 ;
                if ( (add + mid * mul) <= n ) l = mid ;
                else r = mid - 1 ;
            }
            ans += l;
        }
    }
    cout << ans << '\n';
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tt = 1 ;
    cin >> tt ;
    while( tt-- ) {
        AC();
    }
}

//  1  2  3 4 5 6 7 ....n
