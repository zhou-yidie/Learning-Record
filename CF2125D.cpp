#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

struct Segment {
    int l, r;
    long long prob;
    
    bool operator<(const Segment& other) const {
        return l < other.l;
    }
};

long long modPow(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

long long modInverse(long long a) {
    return modPow(a, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<Segment> segments(n);
    for (int i = 0; i < n; i++) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        segments[i] = {l, r, (long long)p * modInverse(q) % MOD};
    }
    
    // 按左端点排序
    sort(segments.begin(), segments.end());
    
    // P[i] 表示区间 [1,i] 都没有被覆盖的概率
    vector<long long> P(m + 1, 1);
    for (int i = 0; i < n; i++) {
        int l = segments[i].l;
        long long prob = segments[i].prob;
        P[l] = P[l] * (1 - prob + MOD) % MOD;
    }
    
    // 计算前缀积
    for (int i = 1; i <= m; i++) {
        P[i] = P[i - 1] * P[i] % MOD;
    }
    
    // dp[i] 表示区间 [1,i] 被恰好一个segment覆盖的概率
    vector<long long> dp(m + 1, 0);
    dp[0] = 1;
    
    for (int i = 0; i < n; i++) {
        int l = segments[i].l;
        int r = segments[i].r;
        long long p = segments[i].prob;
        
        // 关键公式：dp[r] += dp[l-1] * P[r] / P[l-1] / (1-p) * p
        long long tmp = dp[l - 1] * P[r] % MOD;
        tmp = tmp * modInverse(P[l - 1]) % MOD;
        tmp = tmp * modInverse(1 - p + MOD) % MOD;
        tmp = tmp * p % MOD;
        
        dp[r] = (dp[r] + tmp) % MOD;
    }
    
    cout << dp[m] << '\n';
    
    return 0;
}

