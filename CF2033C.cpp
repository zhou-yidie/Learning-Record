#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 2e5 + 10;
int  n,a[N],ans;
void AC() {
    cin >> n;
    ans = 0 ;
    for (int i = 1; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 2; i <= n/2; i ++) {
        int j = n+1-i;
        if (a[i] == a[i-1] || a[j] == a[j+1]) {
            swap(a[i],a[j]);
        }
    }
    ans = 0;
    for (int i = 1; i < n ; i++) {
        if (a[i] == a[i+1]) {
            ans++;
        }
    }
    cout << ans << '\n';
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
