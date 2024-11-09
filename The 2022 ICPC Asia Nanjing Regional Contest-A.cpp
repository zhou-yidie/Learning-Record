#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
 
using namespace std;
const int N=1010;
int n,m,k;
string s;
int U,D,L,R,u,d,l,r;
bool vis[N][N];
int f[N][N];
 
void add(int x1,int y1,int x2,int y2)
{
	f[x1][y1]++;
	f[x2+1][y1]--;
	f[x1][y2+1]--;
	f[x2+1][y2+1]++;
}
void solve()
{
	memset(f,0,sizeof f);
	memset(vis,0,sizeof vis);
	cin>>n>>m>>k>>s;
	U=L=u=l=1;
	R=r=m;
	D=d=n;
	for(int i=0;s[i];i++)
	{
		if(s[i]=='D')u--,d--;
		else if(s[i]=='U')u++,d++;
		else if(s[i]=='L')r++,l++;
		else r--,l--;
		L=max(L,l);
		R=min(R,r);
		U=max(U,u);
		D=min(D,d); 
	}
	
	if(L>R||U>D)
	{
		if(k)cout<<0<<endl;
		else cout<<m*n<<endl;
		return;
	}
	int delta=(D-U+1)*(R-L+1)-k;
	if(delta<0)
	{
		cout<<0<<endl;
		return;
	}
	
	add(U,L,D,R);
	vis[L][U]=1;
	for(int i=0;s[i];i++)
	{
		if(s[i]=='L')L--,R--;
		else if(s[i]=='R')L++,R++;
		else if(s[i]=='U')U--,D--;
		else U++,D++;
		if(vis[L][U])continue;
		vis[L][U]=1;
		add(U,L,D,R); 
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(f[i][j]==delta)ans++;
		}
	}
	cout<<ans<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve(); 
	}
}
