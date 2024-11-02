#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 3e5+50 , mod = 1e9+7;

LL n , m , q ,ans ;

struct  cmp {
    bool operator() ( pair<LL,LL> xa , pair<LL,LL> xb ) {
        if (xa.first == xb.first) return xa.second < xb.second ;
        return xa.first > xb.first ;
    }
};
map< LL , vector<int> > mp;
map<LL,LL > dp;

LL dfs(LL now) {
    if (dp[now]) return dp[now];
    LL res = now ;
    for (int i : mp[now]) {
        res = max(res , dfs(now+i)) ;
    }
    return dp[now] = res ;
}

void AC() {
    cin >> n ; ans = n ;
    //priority_queue< pair<LL,LL> , vector<pair<LL,LL>> , cmp > qu;
    mp.clear(); dp.clear();
    for (LL i = 1 , x; i <= n ; i++) {
        cin >> x ;
        if (i!= 1 && x >= (n-i+1)) {
            mp[ x - (n-i+1) ].push_back(i-1);
        }
    }
    ans+=dfs(0);
    cout <<   ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}