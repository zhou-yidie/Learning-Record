#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
typedef long long ll;

const int inf=0x3f3f3f3f;

int n,a[N],lst,now,T;
ll ans;

int AC(){
	cin>> n ;
	for(int i=1;i<=n;i++)
		cin >> a[i];

	sort(a+1,a+n+1);

	if (n==1) return printf("%d\n",a[1]);

	now=a[1];
	for(int i=2;i<=n;i++)
		now=__gcd(now,a[i]);

	ans=1ll*now*n+(a[1]-now);

	lst=a[1];
	int tmp=now;
	while (true){
		now=inf;
		for(int i=1;i<=n;i++)
			now=min(now,__gcd(lst,a[i]));

		lst=now;
		ans+=lst-tmp;

		if (lst==tmp) break;
	}

	return printf("%lld\n",ans);
}

int main(){
	cin>>T;
	while (T--) AC();

	return 0;
}