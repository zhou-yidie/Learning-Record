#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
using namespace std;
using LL = long long;

const int maxn = 3e5 + 5;
LL n, mod;
int sq;
bool isPrime[maxn];
int primes[maxn], cnt;
void init(){
    isPrime[1] = 1;
    for(int i = 2; i <= sq; i++){
        if (!isPrime[i]) primes[++cnt] = i;
        for(int j = 1; i * primes[j] <= sq; j++){
            isPrime[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}	

LL w[maxn];
int m;
int id1[maxn], id2[maxn];
LL g[maxn];

int get(LL x){
    if (x < maxn) return id1[x];
    return id2[n / x];
}

LL qpow(LL a, LL b){
    LL ans = 1;
    while(b){
        if (b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

LL ans[15];

void dfs(int u, LL mul, int w){
    // 增加最后一个质因子
    // 选择1: 加上一个新的质因子
    // 选择2: 选择跟上一个相同的质因子
    {
        ans[w + 1] += g[get(n / mul)] - (u - 1);
        ans[w] += 1;
    }
    if (u == cnt + 1) return;
    for(int j = u; j <= cnt; j++){
        if (mul * primes[j] * primes[j] > n) break;
        LL val = mul * primes[j];
        while(val <= n){
            if (val * primes[j] <= n) dfs(j + 1, val, w + 1);
            val *= primes[j];
        }
    }
}

int main(){

#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> mod;
    sq = sqrt(n);
    while(1LL * (sq + 1) * (sq + 1) <= n) sq++;
    while(sq * sq > n) sq--;
    init();
    for(LL l = 1, r; l <= n; l = r + 1){
        LL v = n / l;
        r = n / v;
        w[++m] = v;
        if (v < maxn) id1[v] = m;
        else id2[n / v] = m;
        g[m] = v - 1;
    }
    for(int i = 1; i <= cnt; i++){
        for(int j = 1; j <= m and 1LL * primes[i] * primes[i] <= w[j]; j++){
            g[j] -= g[get(w[j] / primes[i])] - (i - 1);
        }
    }

    dfs(1, 1, 0);
    LL res = 1;
    for(int i = 2; i <= 10; i++){
        res = res * qpow(i, ans[i]) % mod;
    }
    cout << res << '\n';

}