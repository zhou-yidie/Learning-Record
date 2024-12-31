#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , k;
unsigned long long ans;
vector<pii> v;
char mp[3030][3030];
LL vis[3030][3030],hh[3030][3030];
map<pii,int> pm;
const int dx[] = { 1 , -1 , 0 , 0 } , dy[] = { 0 , 0 , 1 , - 1 };

struct cmp {
    bool operator() (array<LL , 3> a, array<LL , 3> b) {
        return a[0] >b[0];
    }
};

void AC() {
    cin >> n >> m >> k ; ans = 0 ;
    for (int i = 0; i <= n ; i++) {
        for (int j = 0; j <= m; j++) {
            vis[i][j] = 1e9+7;
        }
    }
    priority_queue< array<LL , 3> ,std::vector<array<LL , 3>>, cmp > qu;
    for (int i = k,x , y; i >= 1; i--) {
        cin >> x >> y ;
        v.push_back({x,y});
        hh[x][y] = i; // [x][y] = i [i][x][y]
        if (i == k) {
            qu.push({0,x,y});
            vis[x][y] = 0;
        }
    }
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
        }
    }
    //qu.push({0,v[0].first,v[0].second});
    // for (int i = 1 ; i <= n ; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         cout << vis[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    while (!qu.empty()) {
        auto [cnt, x, y] = qu.top(); qu.pop();
        if (cnt > vis[x][y]) { continue; }
        //cout << "cnt = " << cnt << '\n';
        for (int i = 0 ; i < 4 ; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx <= 0 || nx > n || ny <= 0 || ny > m) { continue; }
            if (mp[nx][ny] == '#') { continue; }
            LL ncnt = max(cnt+1,hh[nx][ny]);
            if (vis[nx][ny] > ncnt) {
                vis[nx][ny] = ncnt ;
                qu.push({ncnt,nx,ny}); 
            }
        }
    }
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1; j <= m; j++) {
            //cout << vis[i][j] << " ";
            if (vis[i][j] == 1e9+7) { continue; }
            unsigned long long tmp = vis[i][j];
            ans += tmp*tmp;
        }
        //cout << "\n";
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int T = 1 ;
    //cin >> T ;
    while (T--) {
         AC();
    }
    return 0;
}