#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef int ll;
typedef __int128 LL;
const ll maxn=200007,ee=1e18,p=998244353;
struct Dsu{
	ll fa[maxn];
	ll fid(ll x){for(;x^fa[x];x=fa[x]=fa[fa[x]]); return x;}
	void merge(ll x,ll y){
		x=fid(x),y=fid(y); if(x==y) return;
		if(x>y) fa[y]=x;
		else fa[x]=y;
	}
}dsu[11];
ll n,m,ans;
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll T=1; cin>>T;
	for(;T--;){
		cin>>n>>m; ans=0;
		for(int i=0;i<=10;i++) iota(dsu[i].fa+1,dsu[i].fa+1+n,1);
		for(int i=1,a,d,k,fr,ed;i<=m;i++){
			cin>>a>>d>>k; if(k==0) continue;
			fr=a,ed=a+d*k;
			for(int j=fr+d;j<=ed;j=dsu[d].fid(j+d)){
				dsu[d].merge(j-d,j);
				if(j+d>ed) break;
				dsu[d].merge(j,j+d);
			}
		}
		for(int j=1;j<=10;j++)for(int i=1;i<=n;i++) dsu[0].merge(dsu[j].fid(i),i);
		for(int i=1;i<=n;i++)if(dsu[0].fid(i)==i) ans++;
		cout<<ans<<"\n";
	}
	return 0;
}
