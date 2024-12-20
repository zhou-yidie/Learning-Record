#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct HLD {
    int n, cur = 0;
    vector<int> sz, top, dep, par, tin, tout, seq;
    vector<vector<int>> adj;
    HLD(int n) : n(n), sz(n, 1), top(n), dep(n), par(n), tin(n), tout(n), seq(n), adj(n) {}
    void add_edge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
    void build(int root = 0) {
        top[root] = root, dep[root] = 0, par[root] = -1;
        dfs1(root), dfs2(root);
    }
    void dfs1(int u) {
        if (auto it = find(adj[u].begin(), adj[u].end(), par[u]); it != adj[u].end()) {
            adj[u].erase(it);
        }
        for (auto &v : adj[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) { swap(v, adj[u][0]); }
        }
    }
    void dfs2(int u) {
        tin[u] = cur++;
        seq[tin[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        tout[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = par[top[u]];
            } else {
                v = par[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
    int jump(int u, int k) {
        if (dep[u] < k) { return -1; }
        int d = dep[u] - k;
        while (dep[top[u]] > d) { u = par[top[u]]; }
        return seq[tin[u] - dep[u] + d];
    }
    // u is v's ancestor
    bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tin[v] < tout[u]; }
    // root's parent is itself
    int rooted_parent(int r, int u) {
        if (r == u) { return u; }
        if (is_ancestor(r, u)) { return par[u]; }
        auto it = upper_bound(adj[u].begin(), adj[u].end(), r, [&](int x, int y) {
            return tin[x] < tin[y];
        }) - 1;
        return *it;
    }
    // rooted at u, v's subtree size
    int rooted_size(int r, int u) {
        if (r == u) { return n; }
        if (is_ancestor(u, r)) { return sz[u]; }
        return n - sz[rooted_parent(r, u)];
    }
    int rooted_lca(int r, int a, int b) { return lca(a, b) ^ lca(a, r) ^ lca(b, r); }
};

// res : parent of each vertex in dominator tree, -1 is root, -2 if not in tree
struct DominatorTree {
    int n, cur = 0;
    vector<int> dfn, rev, fa, sdom, dom, val, rp, res;
    vector<vector<int>> adj, rdom, r;
    DominatorTree(int n) : n(n), dfn(n, -1), res(n, -2), adj(n), rdom(n), r(n) {
        rev = fa = sdom = dom = val = rp = dfn;
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
    void dfs(int u) {
        dfn[u] = cur;
        rev[cur] = u;
        fa[cur] = sdom[cur] = val[cur] = cur;
        cur++;
        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                rp[dfn[v]] = dfn[u];
            }
            r[dfn[v]].push_back(dfn[u]);
        }
    }
    int find(int u, int c) {
        if (fa[u] == u) {
            return c != 0 ? -1 : u;
        }
        int p = find(fa[u], 1);
        if (p == -1) {
            return c != 0 ? fa[u] : val[u];
        }
        if (sdom[val[u]] > sdom[val[fa[u]]]) {
            val[u] = val[fa[u]];
        }
        fa[u] = p;
        return c != 0 ? p : val[u];
    }
    void build(int s = 0) {
        dfs(s);
        for (int i = cur - 1; i >= 0; i--) {
            for (int u : r[i]) {
                sdom[i] = min(sdom[i], sdom[find(u, 0)]);
            }
            if (i > 0) {
                rdom[sdom[i]].push_back(i);
            }
            for (int u : rdom[i]) {
                int p = find(u, 0);
                if (sdom[p] == i) {
                    dom[u] = i;
                } else {
                    dom[u] = p;
                }
            }
            if (i > 0) {
                fa[i] = rp[i];
            }
        }
        res[s] = -1;
        for (int i = 1; i < cur; i++) {
            if (sdom[i] != dom[i]) {
                dom[i] = dom[dom[i]];
            }
        }
        for (int i = 0; i < n; i++) {
            res[rev[i]] = rev[dom[i]];
        }
    }
};

template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree(int n) : n(n), info(4 * n), tag(4 * n) {}
template <typename T>
    LazySegmentTree(vector<T> init) : LazySegmentTree(init.size()) {
        auto go = [&](auto go, int id, int l, int r) -> void {
            if (r - l == 1) {
                info[id] = {init[l]};
                return;
            }
            int m = l + r >> 1;
            go(go, id << 1, l, m);
            go(go, id << 1 | 1, m, r);
            pull(id);
        };
        go(go, 1, 0, n);
    }
    void pull(int id) {
        info[id] = info[id << 1] + info[id << 1 | 1];
    }
    void apply(int id, const Tag &v) {
        info[id] += v;
        tag[id] += v;
    }
    void push(int id) {
        apply(id << 1, tag[id]);
        apply(id << 1 | 1, tag[id]);
        tag[id] = Tag();
    }
    void modify(int p, const Info &v) {
        auto go = [&](auto go, int id, int l, int r) -> void {
            if (r - l == 1) {
                info[id] = v;
                return;
            }
            int m = l + r >> 1;
            push(id);
            p < m ? go(go, id << 1, l, m) : go(go, id << 1 | 1, m, r);
            pull(id);
        };
        go(go, 1, 0, n);
    }
    Info rangeQuery(int ql, int qr) {
        auto go = [&](auto go, int id, int l, int r) -> Info {
            if (qr <= l || r <= ql) {
                return Info();
            }
            if (ql <= l && r <= qr) {
                return info[id];
            }
            int m = l + r >> 1;
            push(id);
            return go(go, id << 1, l, m) + go(go, id << 1 | 1, m, r);
        };
        return go(go, 1, 0, n);
    }
    void rangeApply(int ql, int qr, const Tag &v) {
        auto go = [&](auto go, int id, int l, int r) -> void {
            if (qr <= l || r <= ql) {
                return;
            }
            if (ql <= l && r <= qr) {
                apply(id, v);
                return;
            }
            int m = l + r >> 1;
            push(id);
            go(go, id << 1, l, m), go(go, id << 1 | 1, m, r);
            pull(id);
        };
        go(go, 1, 0, n);
    }
template <typename F>
    int findFirst(int ql, int qr, F f) {
        auto go = [&](auto go, int id, int l, int r) -> int {
            if (qr <= l || r <= ql || !f(info[id])) {
                return n;
            }
            if (r - l == 1) {
                return l;
            }
            push(id);
            int m = l + r >> 1;
            int res = go(go, id << 1, l, m);
            if (res == n) {
                res = go(go, id << 1 | 1, m, r);
            }
            return res;
        };
        return go(go, 1, 0, n);
    }
template <typename F>
    int findLast(int ql, int qr, F f) {
        auto go = [&](auto go, int id, int l, int r) -> int {
            if (qr <= l || r <= ql || !f(info[id])) {
                return -1;
            }
            if (r - l == 1) {
                return l;
            }
            push(id);
            int m = l + r >> 1;
            int res = go(go, id << 1 | 1, m, r);
            if (res == -1) {
                res = go(go, id << 1, l, m);
            }
            return res;
        };
        return go(go, 1, 0, n);
    }
};

constexpr i64 inf = 1e18;

struct Info {
    i64 x = inf, cmin = inf;
};

struct Tag {
    i64 x = inf, y = 0;
};

Info operator+(Info a, Info b) {
    return {min(a.x, b.x), min(a.cmin, b.cmin)};
}

Info& operator+=(Info &a, Tag b) {
    a.x += b.y;
    a.x = min(a.x, b.x + a.cmin);
    return a;
}

Tag& operator+=(Tag &a, Tag b) {
    a.y += b.y;
    a.x += b.y;
    a.x = min(a.x, b.x);
    return a;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int t;
    cin >> t;

    auto solve = [&]() {
        int n, m, q;
        cin >> n >> m >> q;

        DominatorTree dt(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            dt.add_edge(v, u);
        }
        dt.build();

        HLD g(n);
        for (int i = 1; i < n; i++) {
            int j = dt.res[i];
            g.add_edge(i, j);
        }
        g.build();

        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }

        // vector dp(q + 1, vector<i64>(n + 1, inf));
        // dp[0][n] = 0;

        // for (int i = 0; i < q; i++) {
        //     int a, b;
        //     cin >> a >> b;
        //     a--;

        //     dp[i + 1] = dp[i];
        //     i64 x = *min_element(dp[i].begin(), dp[i].end());
        //     for (int j = 0; j <= n; j++) {
        //         dp[i + 1][j] = min(dp[i + 1][j], x + (j < n ? c[j] : inf));
        //     }
        //     for (int j = 0; j < n; j++) {
        //         if (!g.is_ancestor(j, a)) {
        //             dp[i + 1][j] += b;
        //         }
        //     }
        //     dp[i + 1][n] += b;

        //     cout << *min_element(dp[i + 1].begin(), dp[i + 1].end()) << " \n"[i + 1 == q];
        // }

        LazySegmentTree<Info, Tag> st(n + 1);
        for (int i = 0; i < n; i++) {
            st.modify(g.tin[i], {inf, c[i]});
        }
        st.modify(n, {0, inf});

        for (int i = 0; i < q; i++) {
            int a, b;
            cin >> a >> b;
            a--;

            auto mn = st.rangeQuery(0, n + 1).x;
            st.rangeApply(0, n + 1, Tag{mn, 0});

            while (a >= 0) {
                int p = g.top[a];
                st.rangeApply(g.tin[p], g.tin[a] + 1, Tag{inf, -b});
                a = g.par[p];   
            }
            st.rangeApply(0, n + 1, Tag{inf, b});

            cout << st.rangeQuery(0, n + 1).x << " \n"[i + 1 == q];
        }
    };

    while (t--) {
        solve();
    }
    
    return 0;
}