#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e7 + 7;

const int MOD = 998244353;
int fac[N], inv[N];

int fsp(int x, int y) {
    int res = 1;
    while(y) {
        if(y&1) res = (1LL * res * x) % MOD;
        x = (1LL * x * x) % MOD;
        y >>= 1;
    }
    return res;
}

void init() {
    fac[0] = inv[0] = 1;
    for(int i=1; i<N; i++) fac[i] = (1LL * fac[i-1] * i) % MOD;
    inv[N-1] = fsp(fac[N-1], MOD-2);
    for(int i=N-2; i>=1; i--) inv[i] = (1LL * inv[i+1] * (i+1)) % MOD;
}

int get(int n, int m) {
    if (m > n || m < 0) return 0;
    return (1LL * fac[n] * inv[m] % MOD) * inv[n-m] % MOD;
}

int getinv(int n, int m) {
    if (m > n || m < 0) return 0;
    return (1LL * fac[m] * fac[n-m] % MOD) * inv[n] % MOD;
}

void AC() {
    vector<int> a;
    int n, odd = 0; 
    cin >> n;
    for(int i=1; i<=n; i++) {
        char opt; 
        int x;
        cin >> opt >> x;
        if(x & 1) odd += 1;
        a.push_back(x);
    }
    
    if(odd >= 2) {
        cout << inv[2] << "\n";
    } else {
        int p = 1, tot = 0;
        for(int i : a) tot += i;
        
        for(int i : a) {
            // 确保不会出现负数或无效值
            if (tot <= 0) break;
            long long term1 = get(tot/2, i/2);
            long long term2 = getinv(tot, i);
            p = (1LL * p * term1 % MOD) * term2 % MOD;
            tot -= i;
        }
        
        int res;
        if(!odd) 
            res = (1LL + MOD - p) * inv[2] % MOD;
        else 
            res = (1LL + p) * inv[2] % MOD;
        // 确保结果为正数
        cout << (res + MOD) % MOD << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int _ = 1;
    cin >> _;
    init();
    while (_--) {
       AC(); 
    }
    return 0;
}