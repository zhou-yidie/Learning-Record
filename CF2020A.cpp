#include <bits/stdc++.h>
using namespace std;
int jzzh(int x,int y){
	string sum="";
	int b;
	string a;
	while(x){
		b=x%y;
		a=to_string(b);
		x/=y;
		sum=a+sum;
	}
	return stoi(sum);
}
int main() {
	int n,t,k,c;
	cin>>t;
	for(int i=0; i<t; i++) {
		int count=0;
		cin>>n>>k;
		if(k==1){
			cout<<n<<endl;
			continue;
		}
		//c=jzzh(n,k);
		while(n){
			count += n % k;
			n /= k;
		}
		cout<<count<<endl;
	}
	return 0;
}
