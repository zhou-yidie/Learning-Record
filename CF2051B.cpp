#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , a , b , c;


void AC() {
    cin >> n >> a >> b >> c;
    LL ans = 0;
    ans += (n/(a+b+c))*3;
    n %= (a+b+c);
    // cout << "ans = " << ans << '\n';
    if (n > 0) ans += 1;
    if (n > a) ans += 1;
    if (n > a+b) ans += 1;
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