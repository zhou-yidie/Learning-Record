#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;

    map<ll, ll> freq;
    for (auto &x : a) freq[x]++;

    sort(a.begin(), a.end());
    ll l = 0, ans = 0;
    for(ll r=0;r<n;r++) {
        l = max(l, r);
        while(l + 1 < n and a[l+1] - a[l] <= 1 and a[l+1] - a[r] < k) 
            l++;
        ans = max(ans, l - r + 1);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

