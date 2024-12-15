#include<bits/stdc++.h>
#define LL long long

using namespace std;
const int N=5e5+100;
LL n,k,sm ,ans;
string s ;
LL dp[1010];
void solve(){
    cin >> n >> s ; s += " " ;
    string cur = " ";
    int yi = 0 , ling = 0 , j = 0 ;
    for (int i = 0 ; i < n ;i ++ ) {
        if (s[i] == '1') {
            cur += '1'; yi++ ;
        } else {
            j = i ;
            while (s[j] == '0') {
                j++ ;
            }
            i = j-1;
            cur += '0' ;
            ling++ ;
        }
    }
    if (yi > ling) cout << "Yes\n";
    else cout << "No\n";
    return ;
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
