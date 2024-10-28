// made by djsksbrbf, 2024
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
#define pb push_back
#define po pop_back()
const int MOD = 1e9 + 7;
const int MODD = 998244353;
const int MAX = 2e5 + 5;
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int tc; cin >> tc;
	while(tc--){
		ll ans = 0;
		int n; cin >> n;
		for(int i = 1 ; i <= n ; i++){
			ll num; cin >> num;
			if(i % 2)ans += num;
			else ans -= num;
		}

		cout << ans << endl;
	}
	
	return 0;
}
