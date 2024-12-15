#include<iostream>
using namespace std;
const int N=110;
int a[N];

int main(){
	int n;
	cin>>n;
	for(int i=n;i>=0;i--) cin>>a[i];
    bool flag=0;
	for(int i=n;i>=0;i--) 
	{
		if(a[i]==0) continue;
		if(i==n)
		{
			if(a[i]<0) cout<<"-";
		}
		else
		{
			if(a[i]>0) 
            {
                if(flag) cout<<"+";
            }
			else cout<<"-";
		}
		if((a[i]==1 || a[i]==-1) && i!=0);
		else cout<<abs(a[i]);
		
		if(i!=1 && i!=0) cout<<"x^"<<i;
		else if(i==1) cout<<"x";
        
        flag=1;
	}
	
	
	return 0;
}
//https://ac.nowcoder.com/acm/problem/16622
