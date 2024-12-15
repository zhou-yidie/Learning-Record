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
    cin >> l >> r ;
    // for (int j = 3 ; j <= 7 ; j+=2) {
    //     for (int k = j ; k <= 35 ; k++) {
    //         l = j , r = k;
    //         for (int i  = l ; i <= r ; i++ ) {
    //             vis[i] = false;
    //         }
    //         fg = false;
    //         dfs(l , 1);

    //         cout << " l = " << l << " r = " << r << " fg = " << fg << '\n';
    //     }
    // }
    
    if ( ( r % l ) & 1 && l != 1 ) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }

    // if (l & 1) {
    //     if (r >= 2 * l - 1) {
    //         cout << "Alice\n";
    //     } else {
    //         if ((r-l) & 1) {
    //             cout << "Bob\n";
    //         } else {
    //             cout << "Alice\n";
    //         }
    //     }
    // } else {
    //     if (r >= 3 * l + 2) {
    //         cout << "Alice\n";
    //     } else {
    //         if ((r-l) & 1) {
    //             cout << "Bob\n";
    //         } else {
    //             cout << "Alice\n";
    //         }
    //     }
    // }
    // if ((r-l) & 1) {
    //     if (l == 1 ) {
    //         cout << "Alice\n";
    //     } else {
    //         cout << "Bob\n";
    //     }
    // } else {
    //     if (l == 1 ) {
    //         cout << "Bob\n";
    //     } else {
    //         cout << "Alice\n";
    //     }
    // }
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