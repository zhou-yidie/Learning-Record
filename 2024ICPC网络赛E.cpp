#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define int long long
#define ll long long
const ll N = 5e5 + 10;
const int inf = 0x3f3f3f3f;


void solve() {
    int n, m, D;
    cin >> n >> m >> D;
    //assert(D > 0);

    vector<vector<int>> E(n + 1);
    vector<array<int, 2>> from(n+1,array<int, 2>{0,0});
    vector<array<int, 2>> val(n+1,array<int, 2>{inf,inf});

    while (m--) {
        int u, v;
        cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }

    queue<pii> Q;

    int k;
    cin >> k;
    while (k--) {
        int x;
        cin >> x;
        //assert(x != 1);
        val[x][0] = 0;
        Q.push({ 0, x });
    }

    while (!Q.empty()) {
        auto [d, u] = Q.front();
        Q.pop();
        if (d < D) {
            ++d;
            for (auto& v : E[u]) {
                if (val[v][d & 1] != inf) continue;
                val[v][d & 1] = d;
                Q.push({ d, v });
            }
        }
    }

    // from[1][0] = from[1][1] = -1;
    Q.push({ 0, 1 });
    while (!Q.empty()) {
        auto [d, u] = Q.front();
        Q.pop();

        if (u == n) {
            vector<int> path;
            cout << d << '\n';
            int u = n;
            while (d>=0) {
                path.push_back(u);
                u = from[u][d & 1];
                d--;
            }

            //assert(d == path.size() - 1);
            //cout << path.size() - 1 << '\n';
            for (int i = path.size() - 1; i >= 0; --i) {
                cout << path[i] << ' ';
            }
            cout << '\n';
            return;
        }

        ++d;
        for (auto& v : E[u]) {
            if (d >= val[v][d & 1]) continue;
            if (from[v][d & 1]) continue;
            from[v][d & 1] = u;
            Q.push({ d, v });
        }
    }

    cout << "-1\n";
}

signed main() {
    int T = 1;
    cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}
