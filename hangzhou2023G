#include<iostream>
#include<bits/stdc++.h>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL ;typedef pair < int , int > pii ;
typedef unsigned long long ULL ;
const int N = 3e3+5 , INF = 1e9 + 7 ;const double eps = 1e-4 ;
LL n , m , k ;
string s[ N ] ;
int hh[ N ][ N ] , dst[ N ][ N ] ;
const int dx[] = { 1 , -1 , 0 , 0 } , dy[] = { 0 , 0 , 1 , - 1 };

void bfs( int x , int y ){
priority_queue< pair < int , pii > > q ;
q.push( { 0 , { x , y } } ) ;
dst[ x ][ y ] = 0 ;
while( !q.empty() ){
auto[ cost , e ] = q.top() ;
cost = -cost ;
q.pop() ;
tie( x , y ) = e ;
if( cost != dst [ x ][ y ] ) continue ;
for( int i = 0 ; i < 4 ; i ++ ){
int nx = x + dx[ i ] , ny = y + dy [ i ] ;
if( nx < 0 || ny < 0 || nx >= n || ny >= m ) continue ;
if( s[ nx ][ ny ] == '#' ){
continue ;
}
int cdy = max( dst [ x ][ y ] + 1 , hh[ nx ][ ny ] ) ;
if( dst [ nx ][ ny ] > cdy ){
dst [ nx ][ ny ] = cdy ;
q.push( { -cdy , { nx , ny } } ) ;
}
}
}
}

void AC(){
cin >> n >> m >> k ;
pii st ;
for( LL i = k , x , y ; i >= 1 ; i -- ){
cin >> x >> y ; x -- ; y -- ;
hh[ x ][ y ] = i ;
if( i == k ){
st = { x , y } ;
}
}
for(LL i = 0 ; i < n ;i ++ ){
cin >> s[ i ] ;
for(LL j = 0 ; j < m ; ++j ){
dst[ i ] [ j ] = INF ;
}
}
bfs( st.first , st.second ) ;
ULL ans = 0 ;

for( LL i = 0 ; i < n ; i ++ ){
for( LL j = 0 ; j < m ; j++ ){
if( dst [ i ][ j ] == INF ) continue ;
ULL tp = dst [ i ] [ j ] ;
ans += tp * tp ;
}
}
cout << ans << endl ;
return ;
}

int main(){

LL t = 1 ;
//cin >> t ;

while( t-- ){
AC();
}


return 0;
}
