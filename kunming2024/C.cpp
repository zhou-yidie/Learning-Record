#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

int mp[1010][1010];

void AC() {
    LL n , k ; cin >> n >> k ;
    LL cnt = 0 , len = 1 ;
    while (1) {
        cnt++ ;
        LL x = 1 + (len-1)/(k-1);
        LL l = 1 , r = k / x + 10 , mid , res = 1 ;
        while (l <= r) {
            mid = (l + r) >> 1 ;
            if ((len + (mid - 1) * x - 1) / (k-1) + 1 == x) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (len + res * x <= n) {
            len += res * x ;
            if (len == n) {
                break ;
            }
        } else {
            len += (n-len) / x * x ;
            break;
        }
    }
    cout << len << '\n';
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