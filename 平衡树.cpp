#include<bits/stdc++.h>
typedef long long LL ;
using namespace std;
const int N = 1e5 + 5   ;
int n , m ;

namespace trie{
    int id = 2 ;
    int ch[ N * 25 ][ 2 ] , sz[ N * 25 ] ;
    int newnode(){
        ch[ id ][ 0 ] = ch[ id ][ 1 ] = sz[ id ] = 0 ;
        return id ++ ;
    }
    void ins( int x , int d ){
        int u = 1 ;
        for( int i = 25 - 1 ; i >= 0 ; i -- ){
            int v = ( x >> i ) & 1 ;
            if( !ch[ u ][ v ] ) ch[ u ][ v ] = newnode() ;
            u = ch[ u ][ v ] ;
            sz[ u ] += d ;
        }
    }

    int kth( int k ){
        int u = 1 , x = 0 ;
        for( int i = 24 ; i >= 0 ; i-- ){
            if( sz[ ch[ u ][ 0 ] ] >= k ){
                u = ch[ u ][ 0 ] ;
            }else{
                x |= ( 1 << i ) ;
                k -= sz[ ch [ u ][ 0 ] ] ;
                u = ch[ u ][ 1 ] ;
            }
        }
        return x ;
    }

    int nlt( int x ){
        int ans = 0 , u = 1 ;
        for( int i = 24; i >= 0 ; i -- ){
            if( ( x >> i ) & 1 ){
                ans += sz[ ch[ u ][ 0 ] ] ;
                u = ch[ u ][ 1 ] ;
            }else{
                u = ch[ u ][ 0 ] ;
            };
            if( !u ) break;
        }
        return ans ;
    }

    void clear(){
        ch[ 1 ][ 0 ] = ch[ 1 ][ 1 ] = 0 ;
        id = 2 ;
    }

    int pre( int x ){
        int ans = kth( nlt( x ) ) ;
        return ans ;
    }

    int next( int x ){
        int ans = kth( nlt( x + 1 ) + 1 ) ;
        return ans ;
    }

} ;
const int num = 10000000 ;
void AC(){
    cin >> n  ;
    for( int i = 1 ; i <= n ; i++ ){
        int opt , x ; cin >> opt >> x ;
        switch( opt ){
            case 1 : trie::ins( x + num , 1 ) ; break ;
            case 2 : trie::ins( x + num , -1 ) ; break ;
            case 3 : cout << ( trie::nlt( x  + num ) + 1 ) << endl;  break ;
            case 4 : cout << ( trie::kth( x ) - num ) << endl; break ;
            case 5 : cout << ( trie::pre( x + num ) - num ) << endl;; break ;
            case 6 : cout << ( trie::next( x + num ) - num ) << endl;; break ;
        }
    }

    return ;
}

signed main(){

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1;
//	cin >> t;
    while(t --){
        AC();
    }
}
