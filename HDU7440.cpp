#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 1e3+50 , mod = 1e9+7;

LL n , k , ans ;

void AC() {
    cin >> n >> k ; ans = 1;
    for (int i = 1 ; i <= k ; i++ ) {
        if (n & 1) ans *= 12 ;
        else ans *= 4;
        n >>= 1;
    }
    cout << ans << '\n';
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