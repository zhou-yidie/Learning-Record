#include<bits/stdc++.h>
#define LL long long

using namespace std;
const int N=5e5+100;
LL n,k,sm ,ans,cnt;
string s ;
bool wei[66];
LL dp[66];
vector<int> er;

void dfs(LL now) {
    cout << now << " " ;
    if (now >= n) return ;
    LL tp = 0 ;
    for (int i = 0 ; i < er.size(); i ++ ) {
        if (wei[er[i]]) { wei[er[i]] = false ; }
        else {
            wei[er[i]] = true ;
            tp += dp[er[i]];
        }
    }
    for (LL i = er.size() - 1 ; i >= 0 && tp <= now ; i--  ) {
        tp += dp[ er[i] ] ; wei[ er[i] ]  = true;
    }
    dfs(tp);
}

void solve(){
    cin >> n ; k = n ; ans = 0 ;
    cnt = 0 ;
    er.clear();
    while (k) {
        if (k & 1) ans++,er.push_back(cnt);
        k >>= 1; cnt++;
    }
//    cout << n << " " << cnt << '\n';
//    return;
    dp[0] = 1; LL tp = 1 ; wei[0] = false;
    for (int i = 1; i <= 60 ; i++ ) {
        tp*=2;
        dp[i] = tp;
        wei[i] = false;
    }
    if (ans == 1) {
        cout << "1\n1\n";
    } else {
        cout << (int)(er.size()+1) << '\n';
        LL cur = 0 ;
        for (LL i = er.size() - 1, j=0; i >= 0 ; i--,j++ ) {
            if (j & 1) cur += dp[er[i]] , wei[er[i]] = true ;
        }
        //cout << cur << '\n';
        dfs(cur) ;
        cout << '\n';
    }
    er.clear();
    //cout << ""
}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int T=1;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
