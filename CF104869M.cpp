#include <iostream>
#include <algorithm>
#include <string>
#include <assert.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 3;
const int mod = 1e9 + 7;
const int inv3 = 333333336;
string s, t;
int k;
ll p[N];
long long fp(long long base,long long exponent)
{
    long long result=1;
    for(;exponent>0;exponent>>=1)
    {
        if(exponent&1)
            result=result*base%mod;
        base=base*base%mod;
    }
    return result;
}
int solve()//已将S调整为S异或T，且长度调整为偶数
{
    if (s.size() == 2 && s == "00")
        return (fp(4,k-1)-1+mod)%mod*4ll%mod*inv3%mod;
    int cnt=0;
    while(cnt<s.size() && s[cnt]=='0')
        ++cnt;
    if(cnt<k*2-2)
        return -1;
    ll ans = 0;
    for (int i = 1; i < s.size(); i += 2)
    {
        ll t;
        if (s[i - 1] == '0' && s[i] == '0')
            t = 0;
        else if (s[i - 1] == '1' && s[i] == '0')
            t = 1;
        else if (s[i - 1] == '1' && s[i] == '1')
            t = 2;
        else
            t = 3;
        ans += p[i / 2] * t % mod;
        if (ans >= mod)
            ans -= mod;
    }
    return (ans+(fp(4,k-1)-1+mod)%mod*4ll%mod*inv3%mod)%mod;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    p[0] = 1;
    for (int i = 1; i < N; ++i)
        p[i] = (p[i - 1] * 4 + 1) % mod;
    int T;
    cin >> T;
    for (int kase = 1; kase <= T; ++kase)
    {
        cin >> s >> t >> k;
        reverse(s.begin(), s.end());
        reverse(t.begin(), t.end());
        while (s.size() < t.size())
            s += "0";
        while (t.size() < s.size())
            t += "0";
        for (int i = 0; i < s.size(); ++i)
            s[i] = (s[i] == t[i] ? '0' : '1');
        while (s.size() > 1 && s.back() == '0')
            s.pop_back();
        if (s.size() % 2 == 1)
            s += "0";
        cout << solve() << "\n";
    }
    return 0;
}
