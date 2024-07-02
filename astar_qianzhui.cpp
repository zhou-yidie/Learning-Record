#include<bits/stdc++.h>
using namespace  std ;
typedef long long LL ;
typedef pair<int,int> pii ;
const int N = 1e5+10 ;
LL n ;
LL a[N] , c[N];

map<LL , bool > mp ;
map<LL , LL > cnt ;
vector<LL > v;
void AC(){
    cin >> n ;
    LL now = 1 ;
    LL mx = 0 ;
    for( int i = 1 ; i <= n ; i++ ) {
        LL x ; char op ;
        LL l , r ;
        cin >> x >> op ;
        if( op == 'R' ) {
            l = now ;
            r = l + x -1 ;
            now = r ;
        } else {
            r = now ;
            l = r - x + 1 ;
            now = l ;
        }
        if( !mp[ l  ] ) {
            mp[ l  ] = true ;
            v.push_back( l  ) ;
        }
        if( !mp[ r + 1 ] ) {
            mp[ r +1] = true ;
            v.push_back( r+1 ) ;
        }
        //cout << " l = " << l << " r = " << r << endl;
        mx = max( mx , r ) ;
        cnt[ l ] += 1 ;
        cnt[ r + 1 ] -= 1 ;
    }

    sort( v.begin() , v.end() ) ;
    LL pre = 0 ,ans = 0 ;
    //cout << cnt[1] << endl << endl;
    for( int i = 0;  i < v.size() - 1 ; i ++ ) {
        auto nowid = v[ i ] ;
        LL nowval = pre + cnt[ nowid ] ;
        if( nowval % 4 == 1 ) {
            ans += v[i+1] - nowid ;
            //cout << nowid << " " << v[i+1] - nowid << endl;
        }
        pre = nowval ;
    }
    cout << ans << '\n';

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int tt = 1 ;
    //cin >> tt ;
    while( tt-- ) {
        AC();
    }
}
