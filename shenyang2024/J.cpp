#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

bool fg = false;
LL l ,r  ;
bool vis[10010];
void dfs(int cur_x ,  int pos ) {
    bool tp = false;
    // if (cur_x > r) {
    //     if (pos == 0) {
    //         fg = true;
    //     }
    //     return ;
    // }
    for (int i = cur_x ; i <= r ; i+=cur_x) {
        if (!vis[i] && i % cur_x == 0) {
            vis[i] = true;
            tp = true;
            dfs(cur_x+1,1-pos);
            vis[i] = false;
        }
    }
    if (!tp && pos == 1) {
        fg = true;
    }
}

void AC() {
    
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}