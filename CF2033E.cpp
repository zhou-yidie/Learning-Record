#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e6 + 10;

int  n,a[N],b[N],ans;


void AC() {
    cin >> n ;
    for (int i = 1; i <= n ; i++) cin >> a[i],b[i] = 0;;
    int num = 0;
    ans  = 0;
    for (int i = 1; i <= n ; i++) {
        if (a[i] != i && a[a[i]] != i) {
            int tmp = 0;
            int nxt = a[i];
            b[i] = 1;
            while (!b[nxt]) {
                b[nxt] = 1;
                nxt = a[nxt];
                tmp++;
            }
            ans += tmp/2;
        } else {
            b[i] = 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    cin >> _;
    while (_--) {
       AC(); 
    }
    return 0;
}
