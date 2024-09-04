#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define FASTER ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define reps(x,y,z) for(int x=(y);x<(z);x++)
#define ford(x,y,z) for(int x=(y);x>=(z);x--)
#define fords(x,y,z) for(int x=(y);x>(z);x--)
#define VI vector<int>
#define debug(x) cout << endl << "debug=" << "值: "  << x << endl
#define endl "\n"
#define int ll
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const long long N = 1e5+5,INF = 1e9+5;

int t,n;
int a,b,c;
string ss;
void slove()
{//A 65 a 97
	cin >> a >> b >> c;
	cin >> ss;
	for(int k = 0; k < ss.size(); k++){
		if(ss[k] == '-'){
			char x = ss[k-1], y = ss[k+1];
			if((x<='z') && (x >= 'a') && (y<='z') && (y >= 'a') && y >= x){
				string mid = "";
				for(int i = (int)(x+1); i < (int)y; i++){
					if(a == 3){
						for(int j = 1; j <= b; j++){
							mid += '*';
						}
					}
					else if(a == 2)
					{
						for(int j = 1; j <= b; j++){
							char sp = (char)(i-32);
							mid += sp;
						}
					}
					else{
						for(int j = 1; j <= b; j++){
							char sp = (char)(i);
							mid += sp;
						}
					}
				}
				if(c == 2){
					reverse(mid.begin(),mid.end());
				}
				ss.erase(k,1);
				ss.insert(k,mid);
			}
			if((x<='9') && (x >= '0') && (y<='9') && (y >= '0') && y >= x){
				string mid = "";
				for(int i = (int)(x+1); i < (int)y; i++){
					if(a == 3){
						for(int j = 1; j <= b; j++){
							mid += '*';
						}
					}
					else{
						for(int j = 1; j <= b; j++){
							char sp = (char)(i);
							mid += sp;
						}
					}
				}
				if(c == 2){
					reverse(mid.begin(),mid.end());
				}
				ss.erase(k,1);
				ss.insert(k,mid);
			}
		}
	}
	cout << ss << endl;
	return;
}

signed main()
{
	FASTER;
	t = 1;
	//cin >> t;
	while(t--)
	{
		slove();
	}
	
	return 0;
}
//https://ac.nowcoder.com/acm/problem/16644
