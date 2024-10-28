#include<iostream> 
#include<stdlib.h>
#include<sstream>

using namespace std;

long long sum[100010] = {0};  //用于保存sum[i]
long long ans[100010] = {0}; //用于保存sum[i]相等的个数
long long num = 0;
int main(){
	int n;
	int k;
	cin>>n>>k;
	for(int i = 1; i <= n;i++){
		long long t;
		cin>>t;
		sum[i] = (sum[i - 1] + t) % k; //求sum[i] =(a1 + a2 + ...ai)%k;
		num += ans[sum[i]];  //求与当前sum[i]相等的数量；
		ans[sum[i]]++; //sum[i]个数+1;
	}
	cout<<num + ans[0]; //num只保留了区间开始位置不从1开始的，ans[0]为所有下标从1开始的								  
	   				   //区间，相加即为结果
	return 0;
} 

