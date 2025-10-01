#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;

vector<int> pr[N];
int ans[N];

void work(int x) {
    int ma, tmp = x;
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) { ma = i; }
        while (x % i == 0) { x /= i; }
    }
    if (x > 1) { ma = x; }
    pr[ma].push_back(tmp);
    if(ma == tmp) {
        reverse(pr[ma].begin(), pr[ma].end());
        for (int i = 0; i < pr[ma].size(); i++) {
            ans[pr[ma][i]] = pr[tmp][i-1];
        }
        ans[pr[tmp][0]] = pr[tmp][pr[tmp].size()-1] ;
    }
}

void AC() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        ans[i] = i;
    }
    for (int i = n; i >= 2; i--) {
        work(i);
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
    for (int i = 0; i <= n; i++) {
        pr[i].resize(0);
    }
    return ;
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