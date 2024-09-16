#include <bits/stdc++.h>
using namespace std;
vector<int> G[100001];
int sg_status[100001];
void sg(int u, int fa) {
    int res = 0;

    for (auto v : G[u]) {
        if (v == fa)
            continue;
        sg(v, u);
        res^=sg_status[v] + 1;
    }
    sg_status[u] = res;
}
void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        G[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int res = 0;
    sg(1, 0);
    printf("%s", sg_status[1] ? "Alice\n" : "Bob\n");
}
int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}
