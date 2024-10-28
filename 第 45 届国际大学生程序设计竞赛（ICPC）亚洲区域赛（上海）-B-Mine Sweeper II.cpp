#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define FASTER ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define reps(x,y,z) for(int x=(y);x<(z);x++)
#define ford(x,y,z) for(int x=(y);x>=(z);x--)
#define fords(x,y,z) for(int x=(y);x>(z);x--)
#define VI vector<int>
#define debug(x) cout << endl << "debug=" << "值: "  << x << endl
#define endl "\n"
#define int ll
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const long long N = 3e7+5,INF = 1e9+5;
int p[N],n,t,m;
char a[1010][1010] , b[1010][1010];
int ans;
const int codi[ 8 ][ 2 ] = { {1 , 1} , {0 , 1} , {-1 , 1} , {1 , 0}  , {-1 , 0} , {1 , -1} , {0 , -1} , {-1 , -1} };

int get_val( int x_ , int y_ ){
	int val = 0;
	for(int ii = 0; ii < 8 ; ii++){
		int xx = x_ + codi[ii][0] , yy = y_ + codi[ii][1];
		if( xx <= n && xx >= 1 && yy >= 1 && yy <= m ){
			if( a[xx][yy] == 'X' ) val++;
		}
	}
	return val;
}

int get_val_b( int x_ , int y_ ){
	int val = 0;
	for(int ii = 0; ii < 8 ; ii++){
		int xx = x_ + codi[ii][0] , yy = y_ + codi[ii][1];
		if( xx <= n && xx >= 1 && yy >= 1 && yy <= m ){
			if( b[xx][yy] == 'X' ) val++;
		}
	}
	return val;
}


void slove(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
//	int val_a = 0;
//	for(int i = 1; i <= n; i++){
//		for(int j = 1; j <= m; j++){
//			if( a[i][j] == '.' ) val_a += get_val( i , j );
//		}
//	}
	//cout << "val_a = " << val_a << endl;
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> b[i][j];
		}
	}
	
	int val_b = 0;
	
	int cnt = 0;
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if( a[i][j] != b[i][j] ) cnt ++ ;
		}
	}
	
	if( cnt <= ( ( m * n ) / 2 ) ){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				cout << a[i][j];
			}
			cout << endl;
		}
	}
	else{
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				cout <<  ( a[i][j] == 'X' ? '.' : 'X' ) ;
			}
			cout << endl;
		}
	}
	
//	for(int i = 1; i <= n; i++){
//		for(int j = 1; j <= m; j++){
//			b[i][j] =  ( a[i][j] == 'X' ? '.' : 'X' );
//		}
//	}
//	
//	for(int i = 1; i <= n; i++){
//		for(int j = 1; j <= m; j++){
//			if( b[i][j] == '.' ) val_b += get_val_b( i , j );
//		}
//	}
//	
//	cout << "val_b = " << val_b << endl;
//	
//	cout << "\n aaa \n";
//	for(int i = 1; i <= n; i++){
//		for(int j = 1; j <= m; j++){
//			cout << a[i][j];
//		}
//		cout << endl;
//	}
//	cout << "\n bbb \n";
//	for(int i = 1; i <= n; i++){
//		for(int j = 1; j <= m; j++){
//			cout << b[i][j];
//		}
//		cout << endl;
//	}
	
//	for(int i = 1; i <= n; i++){
//		for(int j = 1; j <= m; j++){
//			cin >> b[i][j];
//		}
//	}
//	
//	int val_b = 0;
//	for(int i = 1; i <= n; i++){
//		for(int j = 1; j <= m; j++){
//			if( b[i][j] == '.' ) val_b += get_val_b( i , j );
//		}
//	}
//	cout << "val_b = " << val_b << endl;
	
	return ;
}

signed main(){
	t = 1;
	//cin >> t;
	while(t--){
		slove();
	}
	return 0;
}
