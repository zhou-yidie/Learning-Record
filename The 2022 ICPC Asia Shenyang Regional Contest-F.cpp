#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define PII pair<int, int>
#define int long long 
/*
考虑列01交替的情况，纯净矩阵数为m*(n*n+n)/2,距离一半还需修正
  连续两列1，其他交替，那就多了((n*n+n)/2)个子矩阵
  连续k列1，可以多((n*n+n)/2)*((k*k+k)/2)个。行同理
于是k为((m*m+m)/4)-m 或((n*n+n)/4)-n)即可修正为一半
	修正的前提条件是(m*m+m)%4 == 0 或 (n*n+n)\%4 == 0
*/
string solve(int n)
{
	int aim = (n*n+n)/4 - n; //修正值(需通过连续部分修正)
	int cur = 1;
	string ans = "1";
	for(int i = 0; i < n; i++)
	{
		if(aim >= cur)
		{
			ans.push_back(ans.back()); //连续
			aim -= cur;
			cur++; 
		}
		else
		{
			ans.push_back('1'+'0'-ans.back()); //交替
			cur = 1;
		}
	}
	return ans;
}
 
signed main() 
{
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
    //
    int tt = 1;
    cin >> tt;
    while(tt--)
    {
    	int n, m;
    	cin >> n >> m;
    	if((n*n + n) % 4 == 0) //行交替修正
    	{
    		string s = solve(n);
    		cout << "Yes\n";
    		for(int i = 0; i < n; i++)
    		{
    			for(int j = 0; j < m; j++)
    			{
    				cout << s[i] << " ";
    			}
    			cout << '\n';
    		}
    	}
    	else if((m*m+m) % 4 == 0) //列交替修正
    	{
    		string s = solve(m);
    		cout << "Yes\n";
    		for(int i = 0; i < n; i++)
    		{
    			for(int j = 0; j < m; j++)
    			{
    				cout << s[j] << " ";
    			}
    			cout << '\n';
    		}
    	}
    	else //无法修正
    	{
    		cout << "No\n";
    	}
    }
}
