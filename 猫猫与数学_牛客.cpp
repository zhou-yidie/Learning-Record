#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
ll a, b, ans;
ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}
int main() {
  cin >> a >> b;
  if(a > b) swap(a, b);
  if(gcd(a, b) > 1) {
    cout << 0 << endl;
    return 0;
  }
  b -= a;
  if(!b) {
    cout << 1 << endl;
    return 0;
  }
  if(b == 1) {
    cout << -1 << endl;
    return 0;
  }
  ll ans = 1e18;
  for(ll d = 2; d * d <= b; d ++) {
    if(b % d == 0) {
      ans = min(ans, d - a % d);
      while(b % d == 0) b /= d;
    }
  }
  if(b > 1) {
    ans = min(ans, b - a % b);
  }
  printf("%lld\n", ans);
  return 0;
}

//https://ac.nowcoder.com/acm/contest/54877/E
