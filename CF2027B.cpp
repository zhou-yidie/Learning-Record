#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , q ,ans ;

LL a[2020];

void AC() {
    cin >> n ; ans = n ;
    for (int i = 1; i <= n ; i++) cin >> a[i];
    for (int i = 1 ; i <= n ; i++) {
        LL tmp = i-1;
        for (int j = i+1 ; j<= n ; j++) {
            if (a[j] > a[i]) tmp++;
        }
        ans = min(tmp , ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}