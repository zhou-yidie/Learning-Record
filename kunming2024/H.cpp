#include <bits/stdc++.h>
using namespace std;

#define double long double
#define pi 2 * acos(0)

const int N = 2e5 + 10;
int n, k;
double ang[N];

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            int x, y; cin >> x >> y;
            ang[i] = atan2(y, x);
        }
        if (n == 1) {
            cout << fixed << setprecision(10) << 2 * pi << '\n';
            continue;
        }
        sort(ang + 1, ang + n + 1);
        double ans = 0;
        for (int l = 1; l <= n; l++) {
            int r = l + k;
            if (r > n) {
                r -= n;
                ans = max(ans, 2 * pi + ang[r] - ang[l]);
            } else ans = max(ans, ang[r] - ang[l]);
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
    return 0;
}