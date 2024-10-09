#include<bits/stdc++.h>
std::mt19937 rnd(time(0));
unsigned long long s[200005],v[1000005];
int T,n,m;
int main(){
	for(int i=1000000;i;--i)v[i]=rnd();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1,x;i<=n;++i)
			scanf("%d",&x),s[i]=s[i-1]^v[x];
		for(int l,r;m--;)
			scanf("%d%d",&l,&r),
			puts(s[r]==s[l-1]?"YES":"NO");
	}
	return 0;
}
