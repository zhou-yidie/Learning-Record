#include <iostream>
#define ll long long
using namespace std;

ll query(ll n) {
    ll ret = 0;
    while (n > 0) {
        ret += n / 5;
        n /= 5;
    }
    return ret;
}

int main() {
    ll k;
    cin >> k;
    ll l = 1, r = 0x7fffffffffffffffL; // long long的最大
    while (l < r) {
        ll mid = l + (r - l >> 1);
        if (query(mid) < k) l = mid + 1;
        else r = mid;
    }
    ll ret = query(l);
    if (ret == k) cout << l;
    else cout << -1;
    return 0;
}

//https://www.lanqiao.cn/problems/2145/learning/?page=9&first_category_id=1&sort=students_count&tags=%E7%9C%81%E8%B5%9B
