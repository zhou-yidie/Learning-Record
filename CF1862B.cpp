#include <bits/stdc++.h>
using namespace std;
int a[200010],b[200010];
int main(){
    ios::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0);
	int t,n;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>b[j];
		}
		int count=1;
		for(int j=2;j<=n;j++){
			if (b[j] >= b[j-1]) {
                count++;
            } else {
                count += 2;
            }
		}
		cout<<count<<endl;
		cout<<b[1]<<" ";
		for(int j=2;j<=n;j++){
			if(b[j] >= b[j-1]){
				cout<<b[j]<<" ";
			} else {
				cout<<b[j]<<" "<<b[j]<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
}