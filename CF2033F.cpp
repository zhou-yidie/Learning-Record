#include<bits/stdc++.h> 
using namespace std;
const long long MOD = 1000000007;
int T,k,a1,a2,a3,ans;
long long n;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%lld%d",&n,&k);
		if(k == 1){
			printf("%lld\n",n % MOD);
			continue;
		}
		a1 = a2 = 1;
		for(int i = 3;true;i ++){//用余数递推即可 
			a3 = (a1 + a2) % k;
			if(!a3){
				ans = i;
				break;
			}
			a1 = a2,a2 = a3;
		}
		printf("%lld\n",n % MOD * ans % MOD);
	}
}