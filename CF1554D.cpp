#include<bits/stdc++.h>
#define LL long long

using namespace std;
const int N=5e5+100;
LL n,k,sm; 
string tmp; 

void solve(){
    cin >> n  ;
    string  ans = tmp;
    LL x = n/2-1; 
    for(int i =1; i <= x ; i++) {
            ans  += 'a'; 
     }
     ans+='b'; 
     if (n & 1   &&   n!=1) ans+='c'; 
     for(int i =1; i <= x+1 ; i++) {
            ans  += 'a'; 
     }
     cout  << ans<< '\n'; 
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