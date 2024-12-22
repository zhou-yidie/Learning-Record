#include<bits/stdc++.h>

#define int long long 

using namespace std;

constexpr int inf = 1e18;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> to(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        to[u].push_back(v);
        to[v].push_back(u);
    }
    vector<pair<bitset<250>, pair<int, int>>> g, g2;
    bitset<250> vis;
    vis.set(0, 1);
    g.push_back({vis, {0, 0}});
    vis.set(0, 0);
    auto dfs = [&](auto self, int u, int f, int d, int u2) -> void {
        vis.set(u, 1);
        if(d == k) {
            if(u < u2) {
                g.push_back({vis, {u, u2}});
            }
            return;
        }
        for(auto v : to[u]) {
            if(v == f) continue;
            self(self, v, u, d + 1, u2);
            vis.set(v, 0);
        }
    };
    for(int i = 0; i < n; i++) {
        dfs(dfs, i, -1, 0, i);
        vis.set(i, 0);
    }
    int row = g.size();
    if(row < n) {
        cout << "NO" << endl;
        return;
    }
    g2 = g;
    vector<int> w(n);
    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        for(int j = i; j < row; j++) {
            if(g[j].first[i]) {
                swap(g[j], g[i]);
                break;
            }
        }
        if(!g[i].first[i]) {
            cout << "NO" << endl;
            return;
        }
        for(int j = i + 1; j < row; j++) {
            if(g[j].first[i])
                g[j].first ^= g[i].first;
        }
    }
    cout << "YES" << endl;
    cout << "? " << n - 1 << ' ';
    for(int i = 1; i < n; i++)
        cout << g[i].second.first + 1 << ' ' << g[i].second.second + 1 << ' ';
    cout << endl;
    for(int i = 1; i < n; i++)
        cin >> w[i];
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < row; j++)
            if(g2[j].second == g[i].second) {
                g[i].first = g2[j].first;
                break;
            }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(g[j].first[i]) {
                swap(g[j], g[i]);
                swap(w[j], w[i]);
                break;
            }
        }
        for(int j = i + 1; j < n; j++) {
            if(g[j].first[i]) {
                g[j].first ^= g[i].first;
                w[j] ^= w[i];
            }
        }
    }
    for(int i = n - 1; i >= 1; i--) {
        for(int j = i + 1; j <= n - 1; j++)
            if(g[i].first[j])
                w[i] ^= w[j];
    }
    cout << "! ";
    for(int i = 1; i < n; i++)
        cout << w[i] << ' ';
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}