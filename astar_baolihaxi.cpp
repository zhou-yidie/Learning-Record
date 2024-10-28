#include<bits/stdc++.h>
using namespace  std ;
typedef long long LL ;
typedef pair<int,int> pii ;
const int N = 1e3+10 ;
int n ;
int a[N];
vector<int> v ;

map<int, bool> mp;

void AC(){
    cin >> n ;
    int pre = 0  ;
    for( int i = 1; i <= n ; i++ ){
        cin >> a[ i ] ;
        if( !mp[a[i] ] ) {
            v.push_back( a[ i  ]) ;
            mp[ a[i] ]  = true ;
        }
    }
    int prenum = 0 , ans = 0 ;
    a[ 0 ] = a[ 1 ] ;
    a[n+1] = 1e7;

    for( int i = 1 ; i <= n + 1 ; i++ ){

        if( a[ i ] == a[ i - 1 ] ) {
            prenum ++ ;
        } else {
            //v.push_back( { a[ i -1 ] , prenum } ) ;
            pre = max( pre , prenum ) ;
            prenum = 1 ;
        }

    }

    for(auto val : v ) {
        int preid = 0 ;
        prenum = 0 ;
        for( int i = 1 , cnt = 1 ; i <= n + 1 ; i++ ){
            if( a[ i ] == val ) continue ;
            if( cnt == 1 ){
                prenum++ ;
                preid = i ;
                cnt = 2 ;
                continue ;
            }
            if( a[ i ] == a[ preid ] ) {
                prenum ++ ;
            } else {
                ans = max( ans , prenum ) ;
                prenum = 1 ;
            }
            preid = i ;
        }

       // cout << val << " ; " << ans << '\n';

    }

//    for( auto x : v ) {
//        cout << x.first << " " << x.second << '\n';
//    }
//
//    for( int i = 0 ; i < v.size() - 2 ; i++ ){
//        if( v[i].first == v[i+2].first ){
//            ans = max( ans , v[i].second + v[i+2].second ) ;
//        }
//    }
    cout << ans - pre ;

    return ;
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
