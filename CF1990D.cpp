#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
int n,a[maxn+5],tag1[maxn+5],tag2[maxn+5]; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test;
	cin>>test;
	while(test--){
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i],tag1[i]=tag2[i]=0;
		for(int i=1;i<=n;i++){
			if(!a[i])continue;
			if(tag1[i]&&a[i]<=2)continue;
			if(tag1[i]&&tag2[i]&&a[i]<=4)continue;
			//特判当前这一列被染完的情况 
			if(a[i]<=2){
				tag1[i]=tag1[i+1]=1;
			}else if(a[i]<=4){
				if(tag2[i])tag1[i]=tag1[i+1]=1;//后面的染了染前面 
				else if(tag1[i])tag2[i]=tag2[i+1]=1;//前面的染了染后面
			}
			ans++;
		}
		cout<<ans<<"\n";
	}
	return 0;
}