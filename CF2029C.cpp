#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int N = 3 * 114514, inf = LONG_LONG_MAX / 2 - 100;

int a[N], n, maxn[N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);


    int t ; cin >> t ;
    while (t--) {
        cin >> n;
        for (int i = 1 ;i  <= n ; i++ ) { cin >> a[i]; }
        int x = 0;
        for (int i = 1 ; i <= n ; i++) {
            maxn[i] = max(maxn[i - 1], x); 
            if (a[i] > x) {
                x++;
            } else if (a[i] < x) {
                x--;
            }
        }
        x = 0;
        for (int i = 1 ; i <= n ; i++) {
            x = max(x, maxn[i]);
            if (a[i] > x) {
                x++;
            } else if (a[i] < x) {
                x--;
            }
        }
        x = max(x, maxn[n]);
        if (x == n) {
            x--;
        }
        printf("%lld\n", x);
    }
    return 0;
}