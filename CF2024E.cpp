#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 4e5 + 5;
int t= 1, a[N], b[N], ia[N], ib[N], ca[2], cb[2], n, k, m1, m2, s[N*3], nxt[N*3];
vector <int> g1[N], g2[N];
void dfs(int u, int id[], vector <int> g[]) {
    for(int v : g[u]) if (id[v] == -1) 
        id[v] = (id[u] + 1 ) % k, dfs(v, id, g);
}

bool vis[N];

int main() {
    cin>>t;

    for(int _=1; _ <= t; _++) {
        cin>>n>>k;
        for(int i=1; i<=n; i++) g1[i].clear(), g2[i].clear(), ia[i] = ib[i] = -1;
            for(int i=0; i<k; i++) vis[i] = 0;
        ca[0] = cb[0] = ca[1] = cb[1] = 0;

        for(int i = 1; i<=n; i++) cin>>a[i], ca[a[i]]++;
        cin>>m1;
        for(int i = 1; i<=m1; i++) {
            int u,v;
            cin>>u>>v;
            g1[u].push_back(v);
        }

        for(int i = 1; i<=n; i++) cin>>b[i], cb[b[i]]++;
        cin>>m2;

        for(int i=1; i<=m2; i++) {
            int u,v;
            cin>>u>>v;
            g2[u].push_back(v);
        }

        ia[1] = ib[1] = 0;
        dfs(1, ia, g1);
        dfs(1, ib, g2);

        for(int i=0; i<=3 * k; i++) s[i] = 0;
        for(int i=1; i<=n; i++) if (a[i]) s[ia[i]]++; s[k] = -1;
        for(int i=1; i<=n; i++) if (!b[i]) s[ib[i]+k+1]++, s[ib[i]+k+k+1]++;
        for(int i=1; i<=3*k - 1; i++) {
            int j = nxt[i-1];
            while(j && s[j] != s[i]) j = nxt[j-1];
            if(s[j] == s[i]) j++;
            nxt[i] = j;
            if( i>= 2 * k && nxt[i] == k) vis[i-2*k] = 1;
        }

        for(int i=0; i<=3 * k; i++) s[i] = 0;
        for(int i=1; i<=n; i++) if (b[i]) s[ib[i]]++; s[k] = -1;
        for(int i=1; i<=n; i++) if (!a[i]) s[ia[i]+k+1]++, s[ia[i]+k+k+1]++;
        bool ok = 0;
        for(int i=1; i<=3*k - 1; i++) {
            int j = nxt[i-1];
            while(j && s[j] != s[i]) j = nxt[j-1];
            if(s[j] == s[i]) j++;
            nxt[i] = j;
            if( i>= 2 * k && nxt[i] == k && vis[(k - (i-2*k) + 2) %k]) ok = 1;
        }
            if((!ca[0] || !cb[0]) && (ca[0] + cb[0] == n)) ok = 1;
            cout<< (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
