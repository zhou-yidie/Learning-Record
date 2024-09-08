#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
#define endl '\n'
#define int ll
typedef long long ll;
const int N = 1e7 + 10 , mod = 998244353;
int  n , m ;

int prime[ N / 2 ] , num[ N ] ;
bool noprime[N];

void init(){
    memset( noprime , false , sizeof( noprime ) ) ;
    int sk = 0 ;
    for(int i = 2 ; i <= N ; i++){
        if( !noprime[ i ] ){
            prime[ ++sk ] = i ;
            num[ i ] = 1;
        }

        for( int j = 1 ; j<= sk && i * prime[ j ] <= N ; j++){
            noprime[ i * prime[ j ] ] = 1;
            num[ i *  prime[ j ] ] = num[ i ] + 1;
            if( i % prime[ j ] == 0 ) break;
        }

    }
}

void AC(   ){
    cin >>  n ;
    int ans = 0 ;
    for(int i = 1 ; i <= n ; i++){
        int x ;
        cin >> x ;
        ans ^= num[ x ] ;
    }
    if( ans ){
        cout << "Alice\n";
    }else{
        cout << "Bob\n";
    }

    return ;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    t = 1;
    init();

//    for(int i = 1 ; i <= 100 ; i++){
//        cout << i << "  " << num[ i ] << endl;
//    }

    cin >> t;

    while( t-- ){
        AC();
    }

    return 0;
}
