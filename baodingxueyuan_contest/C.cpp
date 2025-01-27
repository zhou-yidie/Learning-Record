#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , k , ans;


void AC() {
    cin >> n ; ans = 0;
    int l = 0 , r = n ;
    while (l <= r) {
        int mid = (l + r) >> 1;
        LL tmp = (mid *140 + (mid*70)/2 + mid *30) * (6) / 5 ;
        if (tmp <= n) {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    cout << ans << '\n';

}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int T = 1 ;
    //cin >> T ;
    while (T--) {
         AC();
    }
    return 0;
}