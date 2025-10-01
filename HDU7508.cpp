#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 2e5 + 10;




void AC() {
    LL n,k; cin >> n >> k ;
    LL ans = 1;
    for (int i = 1; i <= k ; i++) {
        if (n & 1) ans *= 12;
        else ans *= 4;

        n >>=1;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
       AC(); 
    }
    return 0;
}
