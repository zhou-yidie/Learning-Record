#include<bits/stdc++.h>
using namespace std;
int a[200001]={0};
int fa[200001]={0};  // father 数组
int dfs(int x,int y){     //搜索。
	if(x == 0) return -1;
	if(__gcd(a[x],a[y]) > 1) return x;  //偷一下懒~直接使用gcd函数。
	return dfs(fa[x],y);
}
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++){
		int x,y;
		cin>>x>>y;
		fa[y]=x;  //建树
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x;
		if(x==1){
			cin>>y;
			cout<<dfs(fa[y],y)<<endl;  //搜索
		}
		else{
			cin>>x>>y;
			a[x]=y;
		}
	} 
	return 0;
} 
