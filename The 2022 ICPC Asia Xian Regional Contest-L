#include "bits/stdc++.h"
#define rep(i, z, n) for (int i = z; i <= n; i++)
#define per(i, n, z) for (int i = n; i >= z; i--)
#define ll long long
#define db double
#define PII pair<int, int>
#define fi first
#define se second
#define vi vector<int>
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
using namespace std;
const int N = 2e6 + 10;
int dep[N], son[N];
vector<int> G[N], v;
void dfs1(int now, int d)
{
    for (auto x : G[now])
    {
        dfs1(x, d + 1);
        if (dep[x] > dep[son[now]])
            son[now] = x;
    }
    dep[now] = dep[son[now]] + 1;
}
void dfs2(int now, int d)
{
    if (!son[now])
    {
        v.push_back(d);
    }
    else
    {
        dfs2(son[now], d + 1);
        for (auto x : G[now])
        {
            if (x == son[now])
                continue;
            dfs2(x, 1);
        }
    }
}
void solve()
{
    int n, x;
    cin >> n;
    v.clear();
    for (int i = 1; i <= n; i++)
    {
        G[i].clear();
        dep[i] = son[i] = 0;
    }
    for (int i = 2; i <= n; i++)
    {
        cin >> x;
        G[x].push_back(i);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    int ans = v.size();
    sort(v.rbegin(), v.rend());
    for (int i = 0; i < v.size(); i++)
    {
        ans = min(ans, v[i] + i);
    }
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
