#include<bits/stdc++.h>
using namespace std;
int t,n,z[200];//z数组存储NSEW的个数 
string a;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>a;
		z['N']=z['S']=z['E']=z['W']=0;//多组样例，初始化 
		for(int i=0;i<n;i++){//统计个数 
			z[a[i]]++;
		}//上面讲述的不可行的方案 
		if(z['N']==1&&z['S']==1&&z['E']==0&&z['W']==0||z['N']==0&&z['S']==0&&z['E']==1&&z['W']==1||z['N']%2!=z['S']%2||z['E']%2!=z['W']%2){
			cout<<"NO\n";
			continue;
		}//特判 NSEW的个数都为0时 
		if(z['N']==1&&z['S']==1&&z['E']==1&&z['W']==1){
			for(int i=0;i<n;i++){
				if(a[i]=='N'||a[i]=='S')cout<<'R';//NS给Rower 
				else cout<<'H';//WE给Helicopter 
			}cout<<"\n";
			continue;
		}z['N']/=2;//这些是安排给Rower的NSEW个数，因为int类型会自动舍尾，所以如果有剩下的就自动安排给Helicopter了 
		z['S']/=2;
		z['E']/=2;
		z['W']/=2;
		for(int i=0;i<n;i++){//输出 
			if(z[a[i]]){
				cout<<"R";
				z[a[i]]--;
			}else{
				cout<<"H";
			}
		}cout<<"\n";
	}
	return 0;
}