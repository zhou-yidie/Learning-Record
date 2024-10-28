#include<bits/stdc++.h>
#define eps 1e-5
using namespace std;
typedef long long ll;
const int mod=1e9+7;

int main(){

    int t;
    ll n,m,i=0,j=0,ans=0;
    cin>>n>>m;
    for(i=2;i<=m;i=j+1){
        ll a=n;
        if(i>a) break;
        j=min(a/(a/i),m);
//        cout << "i = " << i << " j = " << j << " sum =  " << (j-i+1)*(a/i) << endl;
        ans = (ans+(j-i+1)*(a/i))%mod;
    }
    for(i=2;i<=m;i=j+1)
    {
        ll a=n-1;
        if(i>a) break;
        j=min((a)/(a/i),m);
//        cout << "i = " << i << " j = " << j   << " sum =  " << (j-i+1)*(a/i) << endl;
        ans = (ans + (j - i + 1) * ( a / i )) % mod;
    }
    ans=(ans + m + n - 1) % mod;
    printf("%lld\n",ans);  
    return 0;
}
