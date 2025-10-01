#include <bits/stdc++.h>
 
using namespace std;
 
using i64 = long long;

int n;
vector<int> a;
vector<vector<int>> e;
vector<array<i64,3>> dp;

void dfs(int u, int fa) {
    i64 sum = 0;
    for (auto &v : e[u]) {
        if (v == fa) {
            continue;
        }
        dfs(v, u);
        sum += dp[v][0];
    }

    i64 up = sum, down = sum;
    for (auto &v : e[u]) {
        if (v == fa) continue;
        up = max(up, sum - dp[v][0] + dp[v][2] + a[v] - a[u]);
        down = max(down, sum - dp[v][0] + dp[v][1] + a[u] - a[v]);
    }

    dp[u] = {up + down - sum, down, up};
    cout << u << " " << dp[u][0] << " " << dp[u][1] << " " << dp[u][2] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> n;
 
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
 
    e.assign(n + 1, vector<int>());
    for (int i = 1; i < n; i += 1) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
 
    dp.assign(n + 1, array<i64,3>());
    dfs(1, 0);

    // for (int i = 1; i <= n; i += 1) {
    //     cout <<  i << " " << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << "\n";
    // }

    cout << dp[1][0] << "\n";
 
    return 0;
}