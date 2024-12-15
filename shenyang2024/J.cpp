#include<bits/stdc++.h>
using namespace std;
#define LL long long
const LL maxn=220000,inf=1LL<<62;
LL n=8,b[maxn]={},c[maxn]={};
struct team{
    string s;LL x;
}a[maxn];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    for(LL i=1;i<=n;i++)cin>>a[i].s>>a[i].x;
    for(LL i=1;i<=4;i++){
        if(a[2*i-1].x>a[2*i].x)b[i]=2*i-1;
        else b[i]=2*i;
    }
    for(LL i=1;i<=2;i++){
        if(a[b[2*i-1]].x>a[b[2*i]].x)c[i]=b[2*i-1];
        else c[i]=b[2*i];
    }
    if(a[c[1]].x<a[c[2]].x)swap(c[1],c[2]);
    cout<<a[c[1]].s<<" beats "<<a[c[2]].s;
    return 0;
}