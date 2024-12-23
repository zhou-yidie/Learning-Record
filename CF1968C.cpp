#include<bits/stdc++.h>
using namespace std;
long long arr[502],x[502];
int main()
{
  long long t,n,i,j;
  cin>>t;
  while(t--)
  {
  	cin>>n;
  	for(i=2;i<=n;i++)
  	{
  		cin>>x[i];
	  }
	arr[1]=502;
	for(i=2;i<=n;i++)
	{
		arr[i]=arr[i-1]+x[i];
	 } 
	 for(i=1;i<=n;i++)
	 	cout<<arr[i]<<" ";
	cout<<"\n";
  }
  return 0;
}
