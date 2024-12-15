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
int p[N],n,t;
string s,ans;

ll f(ll x){
    if(!x) return 1ll;
    if(x % 3) return f(x - 1) + 1;
    else return f(x / 3) + 1;
}
 
void slove(){
    ll l, r;
    cin >> l >> r;
    vector<int> v;
    ll x = r;
    while(x){
        v.push_back(x % 3);
        x /= 3;
    }
    reverse(v.begin(), v.end());
    ll ans = 0;
    for(int i = 0; i < v.size(); i ++){
        ll x = 0;
        for(int j = 0; j < i; j ++)
            x = 3 * x + v[j];
        x = 3 * x + v[i] - 1;
        for(int j = i + 1; j < v.size(); j ++)
            x = 3 * x + 2;
        if(x >= l)
            ans = max(ans, f(x));
    }
 
    cout << max({ans, f(l), f(r)}) << endl;
}   


signed main(){
	t = 1;
	cin >> t;
	while(t--){
		slove();
	}
	return 0;
}
