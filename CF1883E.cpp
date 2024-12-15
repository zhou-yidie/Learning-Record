#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
typedef long long ll;
int n,a[MAXN];
int cz[MAXN];
ll ans;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t){
		--t;
		cin>>n;
		ans=0;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}
		for(int i=2;i<=n;++i){
			int ai=a[i];
			cz[i]=0;
			while((ai>>1)>=a[i-1]){
				ai>>=1;
				--cz[i];
			}
			while(ai<a[i-1]){
				ai<<=1;
				++cz[i];
			}
			cz[i]=max(0,cz[i-1]+cz[i]);
			ans+=cz[i];
		}
		cout<<ans<<'\n';
	}
	return 0;
}
