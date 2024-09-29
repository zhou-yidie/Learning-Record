#include<iostream>
#include<vector>
#define pb push_back
const int N = 3e5 + 10;
std::vector<int> g[N];
int t, n; long long f[N][21], a[N];
void dfs(int x, int fa){
    for(int i = 1; i <= 20; i++) f[x][i] = 1ll * a[x] * i;
    for(auto v:g[x]) if(v != fa){
        dfs(v, x); for(int j = 1; j <= 20; j++){
            long long mx = 9e18;
            for(int k = 1; k <= 20; k++)
                if(j != k) mx = std::min(mx, f[v][k]);
            f[x][j] += mx;
        }
    }
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0),std::cout.tie(0);
    std::cin >> t; while(t--){
        std::cin >> n; long long rs = 9e18;
        for(int i = 1; i <= n; i++) std::cin >> a[i], g[i].clear();
        for(int i = 1, x, y; i < n; i++)
            std::cin >> x >> y, g[x].pb(y), g[y].pb(x);
        dfs(1, 0); long long mx = 9e18;
        for(int i = 1; i <= 20; i++)
        	mx = std::min(mx, f[1][i]);
        std::cout << mx << '\n';
    }
}
