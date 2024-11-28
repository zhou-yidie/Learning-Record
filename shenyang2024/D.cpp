#include<bits/stdc++.h>
using namespace std;
#define LL long long
const LL maxn=2200000;
LL n,ans=0;
LL p[maxn]={},c[maxn]={};
LL a[maxn] , b[maxn] ;
LL lowbit(LL x){
    return x&(-x);
}
void clear(){
    for(LL i=0;i<=n;i++)c[i]=0;
}
void add(LL p,LL v){
    for(;p<=n;p+=lowbit(p))c[p]+=v;
}
LL sum(LL p){
    LL ans=0;
    for(;p;p-=lowbit(p))ans+=c[p];
    return ans;
}
LL ask(){
    LL ans=0;
    for(LL i=n;i;i--){
        ans+=sum(a[i]-1);
        add(a[i],1);
    }
    return ans;
}
LL ask1(){
    LL ans=0;
    for(LL i=n;i;i--){
        ans+=sum(b[i]-1);
        add(b[i],1);
    }
    return ans;
}

LL BF(){
    LL ans=0;
    for(LL i=1;i<=n;i++){
        for(LL j=i+1;j<=n;j++)
            ans+=(p[j]<p[i]);
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1 ; cin >> T ;
    while (T--) {
        scanf("%lld",&n);
        for (int i = 1 ; i <= n ; i++ ) { cin >> a[i] ; }
        for (int i = 1 ; i <= n ; i++ ) { cin >> b[i] ; }
        clear();
        int aaa = ask() & 1 ;
        clear() ;
        int bbb = ask1() & 1;
        //for(LL i=1;i<=n;i++)scanf("%lld",&p[i]);
        //clear();
        //printf("%lld %lld\n",aaa,bbb);
        int res = aaa + bbb ;
        res &= 1;
        if ( res & 1) {
            cout << "A" ;
        } else {
            cout << "B";
        }
        for (int j = 1; j < n ; j ++ ) {
            char c ; int l, r ,d ; cin >> c >> l >> r >> d ;
            if ((r-l) & 1) {
                if (d & 1) {
                    res ++ ;
                } else {

                }
            } else {

            }
            if ( res & 1) {
                cout << "A" ;
            } else {
                cout << "B";
            }
        }
        cout << '\n';
        
    }
    return 0;
}