#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100 , M = 1e9+7 ;
typedef long long LL;

LL f[2][1028] , n , a[N] , p[N] , ans ;

LL qmi(LL aa , LL bb ) {
	LL res = 1 ;
	while (bb) {
		if (bb&1) res = res * aa % M ;
		aa = aa * aa % M ;
		bb >>= 1 ;
	}
	return res ;
}
LL INV = qmi(10000 , M-2) ;

void AC(){
	cin >> n ; 


	for (int j=0;j<=1023;j++){
		f[0][j] = f[1][j] = 0 ;
	}
	
	for (int i = 1 ; i <= n ; i++ ) { cin >> a[i] ; }
	for (int i = 1 ; i <= n ; i++ ) { cin >> p[i] ; }
	f[0][0] = 1 ; ans = 0 ;
	for (int i=1;i<=n;i++){
		for (int j=0;j<=1023;j++){
			f[1][j]+=f[0][j]*(10000-p[i])%M*INV%M;
			f[1][j]=(f[1][j]>=M?f[1][j]-M:f[1][j]);
			f[1][j]+=f[0][j^a[i]]*p[i]%M*INV%M;
			f[1][j]=(f[1][j]>=M?f[1][j]-M:f[1][j]);
		}
		for (int j=0;j<=1023;j++)
			f[0][j]=f[1][j],f[1][j]=0;
	}
	for (int i=0;i<=1023;i++){
		ans+=f[0][i]*i%M*i%M;
		ans%=M;
	}
	cout << ans << '\n';
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0) ;
    int T ;
	cin>>T;
	while (T--) AC();

	return 0;
}