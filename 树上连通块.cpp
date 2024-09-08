#include "bits/stdc++.h"

using namespace std;
#define int long long
vector<vector<int>> adj;
int cnt, mn, n, k;

int dfs(int i, int p) {
    int ret = 1;
    for (auto j: adj[i])if (j != p) ret += dfs(j, i) ;
    cout << " i = " << i << " ret = " << ret << endl ;
    if (ret >= mn)cnt++, ret = 0;
    cout << " i = " << i << " ret = " << ret << endl ;
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;
        adj = vector<vector<int>>(n + 5);
        for (int i = 1, x, y; i < n; i++) {
            cin >> x >> y;
            adj[x].emplace_back(y);
            adj[y].emplace_back(x);
        }
        int l = 1, r = n, md, ans = 0;
        while (l <= r) {
            md = (l + r) / 2;
            cout << " mid = " << md << endl;
            cnt = 0, mn = md, dfs(1, -1);
            if (cnt > k)ans = md, l = md + 1;
            else r = md - 1;
        }
        cout << ans << '\n';
    }
}


// https://codeforces.com/problemset/problem/1946/C
