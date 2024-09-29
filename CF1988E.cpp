#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using pdd = pair<double, double>;
using ull = unsigned long long;
using LL = __int128_t;
using vint = vector<int>;

#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)

bool Mbe;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
//mt19937_64 rnd(1064);
int rd(int l, int r) {
  return rnd() % (r - l + 1) + l;
}

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {
  x += y, x >= mod && (x -= mod);
}
int add(int x, int y) {
  return x += y, x >= mod && (x -= mod), x;
}
int ksm(int a, ll b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(ull((LL(1) << 64) / b)) {}
  ull reduce(ull a) {
    ull q = ull((LL(m) * a) >> 64);
    ull r = a - q * b; // can be proven that 0 <= r < 2 * b
    return r >= b ? r - b : r;
  }
} R(1);

constexpr int Z = 1e5 + 5;
int fc[Z], ifc[Z], inv[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
  for(int i = 1; i < Z; i++) inv[i] = 1ll * fc[i - 1] * ifc[i] % mod;
}

char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
#define putc(x) putchar(x)
inline int read() {
  int x = 0, sgn = 0; char s = getc();
  while(!isdigit(s)) sgn |= s == '-', s = getc();
  while(isdigit(s)) x = x * 10 + s - '0', s = getc();
  return sgn ? -x : x;
}
inline void print(int x) {if(x >= 10) print(x / 10); putc(x % 10 + '0');}

// ---------- templates above ----------

constexpr int K = 19;
constexpr int N = 5e5 + 5;

ll d[N];
int n, a[N], pos[N], stc[N], top, mi[K][N];
int calc(int l, int r) {
  int d = __lg(r - l + 1);
  return min(mi[d][l], mi[d][r - (1 << d) + 1]);
}
int pre(int r, int v) {
  int l = 0;
  while(l < r) {
    int mid = l + r + 2 >> 1;
    if(calc(mid, r) <= v) l = mid;
    else r = mid - 1;
  }
  return l;
}
int suc(int l, int v) {
  int r = n + 1;
  while(l < r) {
    int mid = l + r >> 1;
    if(calc(l, mid) <= v) r = mid;
    else l = mid + 1;
  }
  return l;
}

void dfs(int l, int r) {
  int v = calc(l, r), p = pos[v];
  if(l < p) {
    dfs(l, p - 1);
    ll val = 1ll * v * (p - l) * (r - p + 1);
    d[l] += val, d[p] -= val;
  }
  if(p < r) {
    dfs(p + 1, r);
    ll val = 1ll * v * (p - l + 1) * (r - p);
    d[p + 1] += val, d[r + 1] -= val;
  }
  ll val = 1ll * v * (p - l + 1) * (r - p + 1);
  d[1] += val, d[l - 1] -= val, d[r + 2] += val;
  if(l > 1) {
    int l2 = pre(l - 2, v);
    val = 1ll * v * (p - l2 - 1) * (r - p + 1);
    d[l - 1] += val, d[l] -= val;
  }
  if(r < n) {
    int r2 = suc(r + 2, v);
    val = 1ll * v * (p - l + 1) * (r2 - p - 1);
    d[r + 1] += val, d[r + 2] -= val;
  }
} 
void solve(int T) {
  cin >> n;
  for(int i = 0; i <= n + 3; i++) d[i] = 0;
  for(int i = 1; i <= n; i++) cin >> a[i], mi[0][i] = a[i], pos[a[i]] = i;
  for(int i = 1; i <= __lg(n); i++) {
    for(int j = 1; j + (1 << i) - 1 <= n; j++) {
      mi[i][j] = min(mi[i - 1][j], mi[i - 1][j + (1 << i - 1)]);
    }
  }
  dfs(1, n);
  for(int i = 1; i <= n; i++) {
    cout << (d[i] += d[i - 1]) << " ";
  }
  cout << "\n";
}

bool Med;
signed main() {
  fprintf(stderr, "%.3lf ms\n", 1e3 * clock() / CLOCKS_PER_SEC);
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while(T--) solve(T);
  return 0;
}

/*
g++ a.cpp -o a -std=c++14 -O2 -DALEX_WEI
*/
