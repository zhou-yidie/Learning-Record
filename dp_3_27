#include<bits/stdc++.h>

using namespace std;
const int N =( 1 << 24 )+ 5 ;
#define int long long
int sum[N] , f[N] ;

void solve(){
    int n;
    cin >> n;
    int a[28] = {};
    for (int i = 1;i <= n;i ++)
        cin >> a[i];
    vector<int> c;
    for (int i = 1;i <= n + 1;i ++){
        if (a[i] - a[i - 1] != 0) c.push_back(a[i] - a[i - 1]);
    }
    int num = c.size();

    for (int i = 0;i < (1 << num);i ++){
        for (int j = 0;j < num;j ++)
            if ((i >> j) & 1) sum[i] += c[j];
    }

    for (int i = 1;i <= (1 << num);i ++){
        if (sum[i] == 0) f[i] ++;
        for (int j = 0;j < num;j ++)
            if (!((i >> j) & 1)) f[i | (1ll << j)] = max(f[i | (1ll << j)],f[i]);
    }
    cout << num - f[(1 << num) - 1] << "\n";
}

signed main(){
    //cout << N << endl;
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1;
//	cin >> t;
    while(t --){
        solve();
    }
}

//#include<bits/stdc++.h>

using namespace std;
const int N =( 1 << 24 )+ 5 ;
#define int long long
int sum[N] , f[N] ;

void solve(){
    int n;
    cin >> n;
    int a[28] = {};
    for (int i = 1;i <= n;i ++)
        cin >> a[i];
    vector<int> c;
    for (int i = 1;i <= n + 1;i ++){
        if (a[i] - a[i - 1] != 0) c.push_back(a[i] - a[i - 1]);
    }
    int num = c.size();

    for (int i = 0;i < (1 << num);i ++){
        for (int j = 0;j < num;j ++)
            if ((i >> j) & 1) sum[i] += c[j];
    }

    for (int i = 1;i <= (1 << num);i ++){
        if (sum[i] == 0) f[i] ++;
        for (int j = 0;j < num;j ++)
            if (!((i >> j) & 1)) f[i | (1ll << j)] = max(f[i | (1ll << j)],f[i]);
    }
    cout << num - f[(1 << num) - 1] << "\n";
}

signed main(){
    //cout << N << endl;
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1;
//	cin >> t;
    while(t --){
        solve();
    }
}

//https://contest.ucup.ac/contest/1382/problem/7566
