#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N = 2e6 + 10;
int a[N];
vector<int> to[N];
int dp[N], rt[N << 3], ls[N << 3], rs[N << 3], sz[N << 3];
int sum[N << 3], sum2[N << 3];
 
void update(int id) {
    sum2[id] = sum2[ls[id]] + sum2[rs[id]];
    sum[id] = sum[ls[id]] + sum[rs[id]];
    sz[id] = sz[ls[id]] + sz[rs[id]];
}
int now ;
int merge(int a, int b, int x, int y) {
    if (!a)return b;
    if (!b)return a;
    if (x == y) {
        sz[a] += sz[b];
        sum2[a] += sum2[b];
        sum[a] += sum[b];
        return a;
    }
    int mid = (x + y) >> 1;
    if (ls[a] != 0 && rs[b] != 0) {
       now += sz[ls[a]] * sum2[rs[b]] * 2ll,now -= sum[ls[a]] * sum[rs[b]] * 2ll;
    }
    if (ls[b] != 0 && rs[a] != 0) {
        now+= sz[ls[b]] * sum2[rs[a]] * 2ll, now -= sum[ls[b]] * sum[rs[a]] * 2ll;
    }
    ls[a] = merge(ls[a], ls[b], x, mid);
    rs[a] = merge(rs[a], rs[b], mid + 1, y);
    update(a);
    return a;
}
 
int cnt = 0;
 
int add(int &id, int x, int y, int co) {
    if (!id) id = ++cnt;
    if (x == y) {
        sum2[id] += co * co;
        sum[id] += co;
        sz[id]++;
        return id;
    }
    int mid = (x + y) >> 1;
    if (co <= mid) {
        ls[id] = add(ls[id], x, mid, co);
    } else {
        rs[id] = add(rs[id], mid + 1, y, co);
    }
    update(id);
    return id;
}
 
int ans = 0;
void dfs(int x, int f) {
    int res = 0;
    add(rt[x], 1, 1000000, a[x]);
    for (int i = 0; i < to[x].size(); i++) {
        int v = to[x][i];
        if (v == f)continue;
        dfs(v, x);
        res += dp[v];
        now = 0;
        merge(rt[x], rt[v], 1, 1000000);
        res+=now;
    }
    dp[x] = res;
    ans ^= res;
    return;
}
 
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)cin >> a[i];
    dfs(1, -1);
    cout << ans << '\n';
}
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int _ = 1;
    while (_--) solve();
    return 0;
}