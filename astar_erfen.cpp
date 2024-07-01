#include<bits/stdc++.h>
using namespace  std ;
typedef long long LL ;
typedef pair<int,int> pii ;
const int N = 1e5+10 ;
LL n , l , r , c ;
LL a[N] , b[N];

LL getnum( LL av , LL bv , LL ll , LL rr  ) {
    if( bv  > rr ) { return 0 ; }
    if( ll >= bv ) {
        LL num = 0 ;
        LL st = max((ll - 1 -  bv ) / av , 0LL) , ed = (rr - bv) / av  ;
        num = ed - st ;
        if( ll == bv ) num++;
        return num ;
    }else {
        LL num = 1 ;
        num += ( rr - bv ) / av ;
        return num ;
    }

}

LL check(LL mid ){
    LL sum = 0 ;
    for( int i =1 ; i <= n ; i++ ) {
        LL num = getnum( a[ i ] , b[ i ] , l , mid ) ;
        sum += num ;
        //cout << i << " " << num << '\n';
    }
    return sum ;
}


void AC(){
    cin >> n ;
    for( int i = 1 ; i <= n ; i++) cin >> a[ i ] ;
    for(int i = 1; i  <= n ; i++ ) cin >> b[ i ] ;
    cin >> l >> r >> c ;
    LL sm = 0 ;
    for( int i = 1; i  <= n ; i ++ ){
        sm += getnum( a[ i ] , b[ i ] , l , r  ) ;
    }
    if( sm < c ){
        cout << "-1\n";
        return ;
    }
    //check( 2 ) ;
    LL L = l , R = r ;
    LL ans = r ;
    while( L < R ){
        LL mid = ( L + R ) >> 1 ;
        LL vl = check( mid ) ;
        //cout << L << " " << R << " " << mid << " "  <<  vl << endl ;
        if( vl >= c ) {
            R = mid  ;
            //ans = mid ;
        }else {
            L = mid + 1 ;
        }
    }
    cout << R ;
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
