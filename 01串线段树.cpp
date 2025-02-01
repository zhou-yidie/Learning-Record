#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10 ;
string s ;
struct node {
    int l , r ;
    int v0 , v1 ;
    int rev ;
}tr[ N * 4 ] ;

int len( node &r ) {
    return r.r - r.l + 1 ;
}


void pushup( int u ) {
    int Llen = len( tr[ u << 1 ]) , Rlen = len(tr[ u << 1 | 1 ]) ;
    auto &L = tr[ u << 1 ] , &R = tr[ u << 1 | 1 ] , &RT = tr[ u ] ;
    if ( Llen % 2 == 0 ) {
        RT.v0 = L.v0 + R.v0 ;
        RT.v1 = L.v1 + R.v1 ;
    } else if( Llen % 2 != 0) {
        RT.v0 = L.v0 + R.v1 ;
        RT.v1 = L.v1 + R.v0 ;
    }
}

node pushup( node &L , node &R ) {
    node RT ;
    RT.l = L.l , RT.r = R.r;
    int Llen = len(L) , Rlen = len(R) ;
    if ( Llen % 2 == 0 ) {
        RT.v0 = L.v0 + R.v0 ;
        RT.v1 = L.v1 + R.v1 ;
    } else {
        RT.v0 = L.v0 + R.v1 ;
        RT.v1 = L.v1 + R.v0 ;
    }
    return RT ;
}

void build( int u , int l , int r ) {
    tr[ u ] = { l , r } ;
    if ( l == r ) {
        tr[ u ].v0 = s[ r ] != '0' ;
        tr[ u ].v1 = s[ r ] != '1' ;
        tr[ u ].rev = 0 ;
        return ;
    }
    int mid = ( l + r ) >> 1 ;
    build( u << 1 , l , mid  ) ;
    build( u << 1 | 1  , mid + 1  , r ) ;
    pushup( u ) ;
}

void pushdown( int u ) {
    auto &L = tr[ u << 1 ] , &R = tr[ u << 1 | 1 ] , &RT = tr[ u  ] ;
    if (RT.rev) {
        swap( L .v0 , L.v1 ) ;
        L.rev ^= 1 ;
        swap( R.v0 , R.v1 ) ;
        R.rev ^= 1 ;
        RT.rev = 0 ;
    }
}

void modify( int u , int l , int r ) {
    pushdown( u ) ;
    if (l <= tr[ u ].l && tr[ u ].r <= r) {
        swap( tr[u].v0 , tr[ u ].v1 ) ;
        tr[ u ].rev ^= 1 ;
        return;
    }
    int mid = (tr[ u ].l + tr[ u ].r ) >> 1 ;
    if (l <= mid) {
        modify( u << 1 , l , r ) ;
    }
    if( r > mid ) {
        modify( u << 1 | 1 , l , r ) ;
    }
    pushup( u ) ;
}


node query( int u , int l , int r ) {
    pushdown( u ) ;
    if (l <= tr[ u ].l && tr[ u ].r <= r ) {
        return tr[ u ] ;
    }
    int mid =  ( tr[u].l + tr[u].r ) >> 1 ;
    node L , R ;
    if (r <= mid) {
        return query( u << 1  , l , r ) ;
    } else if ( l > mid ) {
        return query( u << 1 | 1 , l , r ) ;
    } else {
        L = query( u << 1 , l , r ) ;
        R = query( u << 1 | 1 , l , r ) ;
        return pushup( L , R ) ;
    }
}

int main(  ) {
    ios::sync_with_stdio( 0 ) ;
    cin.tie( 0 ) ;  cout.tie( 0 ) ;
    int n , q ; cin >> n >> q  >> s ;
    s = '*' + s ;
    build( 1 , 1 , n ) ;
    while( q-- ) {
        int op , l , r ;
        cin >> op >> l >> r ;
        if ( op == 1 ) {
            modify( 1 , l , r ) ;
        } else {
            auto res = query( 1, l , r ) ;
            cout << min( res.v0 , res.v1 ) << '\n';
        }
    }
    return 0;
}





