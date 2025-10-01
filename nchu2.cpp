#include<bits/stdc++.h>
using namespace std;
const long long NN = 1e5, mod = 998244353;

vector<long long> fac(NN + 1);

void init() {
    fac[1] = 1;
    for (int i = 2; i <= NN; i ++) {
        fac[i] = ( fac[i-1] * i ) % mod;
    }
}

signed main() {
    int t;
    cin >> t;
    init();
    while (t--) {
        int N;
        cin >> N;

        vector<vector<int>> adj(N);
        for (int i = 1; i < N; i++) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        vector<int> d(N);
        vector<vector<int>> subtree(N);
        auto dfs = [&](auto&& self, int x, int p) -> void {
            if (p != -1) {
                adj[x].erase(find(adj[x].begin(), adj[x].end(), p));
            }
            subtree[x].push_back(x);
            for (auto y : adj[x]) {
                d[y] = d[x] + 1;
                self(self, y, x);
                for (auto z : subtree[y]) {
                    subtree[x].push_back(z);
                }
            }
        };
        dfs(dfs, 0, -1);

        auto cal = [&](int n) -> int {
            assert(n != 1);
            return fac[n] - 2 * fac[n - 1] + fac[n - 2];
        };

        int res = 0;
        for (int lca = 0; lca < N; lca++) {
            for (int i = 0; i < adj[lca].size(); i++) {
                for (auto x : subtree[adj[lca][i]]) {
                    int n = d[x] - d[lca] + 1;
                    res += cal(n);
                    for (int j = 0; j < i; j++) {
                        for (auto y : subtree[adj[lca][j]]) {
                            int n = d[x] + d[y] - 2 * d[lca] + 1;
                            res += cal(n);
                        }
                    }
                }
            }
        }
        res += 1;
        cout << (res + N-1) << endl;
    }

    return 0;
}