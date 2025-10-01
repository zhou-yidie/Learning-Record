#include<bits/stdc++.h>

using namespace std;

#define int long long
const int N = 1e5 + 10, M = N << 1;
int n;
int h[N], e[M], ne[M], idx;
int col[N], cnt[N], sz[N], son[N];
int ans[N], sum;
int mx;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int dfs_son(int u, int father)
{
    sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        sz[u] += dfs_son(j, u);/////////
        if (sz[j] > sz[son[u]]) son[u] = j;
    }
    return sz[u];
}

void update(int u, int father, int sign, int pson)
{
    int c = col[u];
    cnt[c] += sign;
    if (mx < cnt[c]) sum = c, mx = cnt[c];
    else if (mx == cnt[c]) sum += c;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == father || j == pson) continue;
        update(j, u, sign, pson);
    }
}

void dfs(int u, int father, int op)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == father || j == son[u]) continue;
        dfs(j, u, 0);
    }
    if (son[u]) dfs(son[u], u, 1);
    update(u, father, 1, son[u]);
    ans[u] = sum;
    if (!op) update(u, father, -1, 0), mx = sum = 0;
}

signed main()
{
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) scanf("%lld", &col[i]);
    int m = n - 1;
    while (m--)
    {
        int x, y; scanf("%lld%lld", &x, &y);
        add(x, y), add(y, x);
    }
    dfs_son(1, -1);
    dfs(1, -1, 1);
    for (int i = 1; i <= n; ++i) printf("%lld ", ans[i]);

    return 0;
}
