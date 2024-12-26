#include<bits/stdc++.h>
#define mp make_pair
typedef long long ll;
using namespace std;
int rev[1000005];
const ll mod=998244353,iv2=(mod+1)>>1;
ll ksm(ll a,int m,int p){
	ll ans=1;
	while(m){
		if(m&1)ans=ans*a%p;
		a=a*a%p;
		m>>=1;
	}
	return ans;
}
static ll w[1000005];
void NTT(ll a[],int n,int type){
	for(int i=0;i<n;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1)rev[i]+=n>>1;
		if(i<rev[i])swap(a[i],a[rev[i]]);
	}
	int m=1;
	ll val;
	if(type>0)val=3;
	else val=ksm(3,mod-2,mod);
	w[0]=1;
	for(m;m<n;m<<=1){
		ll W=ksm(val,(mod-1)/(m+m),mod);
		for(int i=m-2;i>=0;i-=2)w[i]=w[i>>1],w[i+1]=W*w[i]%mod;
		for(int i=0;i<n;i+=m<<1){
			for(int j=i;j<i+m;j++){
				ll v1=a[j],v2=a[j+m]*w[j-i]%mod;
				a[j]=v1+v2;
				a[j]-=a[j]>=mod?mod:0;
				a[j+m]=v1-v2;
				a[j+m]+=a[j+m]<0?mod:0; 
			}
		}
	}
	if(type<0){
		ll mul=ksm(n,mod-2ll,mod);
		for(int i=0;i<n;i++)a[i]=1ll*a[i]*mul%mod;
	}
	return;
}
int Get(int n){
	int res=1;
	while(res<n)res<<=1;
	return res;
}
int T,n;
ll m,f[1200005],g[1200005],res[1200005];
int a[100005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld",&n,&m);
		int base=n;
		for(int i=0;i<=base*8;i++)f[i]=res[i]=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]-=m/n,f[a[i]+base]=1;
		m%=n;
		res[base]=1;
		int N=Get(base<<2);
		while(n>0){
			if(n&1){
				for(int i=0;i<N;i++)g[i]=f[i];
				NTT(g,N,1);
				NTT(res,N,1);
				for(int i=0;i<N;i++)g[i]=res[i]*g[i]%mod;
				NTT(g,N,-1);
				for(int i=0;i<N;i++)res[i]=0;
				for(int i=0;i<base*2;i++)res[i]=g[i+base];
			}
			NTT(f,N,1);
			for(int i=0;i<N;i++)g[i]=f[i]*f[i]%mod;
			NTT(g,N,-1);
			for(int i=0;i<N;i++)f[i]=0;
			for(int i=0;i<base*2;i++)f[i]=g[i+base];
			n>>=1;
		}
		if(res[base+m])puts("Yes");
		else puts("No");
	}
	return 0;
}