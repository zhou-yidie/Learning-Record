#include <bits/stdc++.h>

using namespace std;

namespace FastRead{
	char buf[1000005], *s = buf, *t = buf;
	#define gc() s == t && (t = (s = buf) + fread(buf, 1, 1000000, stdin), s == t) ? EOF : *s ++ 
	template <typename T>
	inline void Read(T &x)
	{
		x = 0;
        int f = 0;
        char ch = gc();
		while(ch < '0' || ch > '9') f = ch == '-', ch = gc();
		while('0' <= ch && ch <= '9') x = x * 10 + ch - 48, ch = gc();
		f && (x = -x);
	}
    inline void Read(char* str)
    {
        char ch = gc();
        while(ch < 32 || ch > 126) ch = gc();
        while(32 <= ch && ch <= 126) *(str ++ ) = ch, ch = gc();
    }
};
using FastRead::Read;

typedef unsigned long long LL;

const int N = 5e5 + 5;

int n, m;
int Map[128];
char s[N];
vector<int> ql[N], qr[N];

const int Base1 = 131;
LL p1[N], h1[N];
int sta[N], tt;
int pos[N], pt[N];
vector<LL> sl, sr;
int emp;

inline void InitHash()
{
    p1[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        p1[i] = p1[i - 1] * Base1;
    }
}
inline LL Calc(int l, int r)
{
    return h1[r] - h1[l - 1] * p1[r - l + 1];
}
inline void Work(vector<LL> &st, vector<int> q[])
{
    tt = 0;
    int lim = 0;
    for(int i = 1; i <= n; i ++ )
    {
        if(s[i] & 1)
        {
            if(s[sta[tt]] != (s[i] ^ 1))
            {
                tt = 0, lim = i;
            }
            else tt -- ;
        }
        else
        {
            sta[ ++ tt] = i;
            h1[tt] = h1[tt - 1] * Base1 + s[i];
        }
        pos[i] = tt;
        pt[i] = sta[tt];

        for(int j : q[i])
        {
            if(j >= lim && tt >= pos[j] && sta[pos[j]] == pt[j])
            {
                if(pos[j] == tt) emp ++ ;
                else st.push_back(Calc(pos[j] + 1, tt));
            }
        }
    }
}

const int Mod = 1 << 21;
struct HashTable{
    LL key[Mod];
    int val[Mod];
    int sta[Mod], tt;
    inline int& operator[](LL x)
    {
        int y = x & (Mod - 1);
        while(key[y] && key[y] != x) ( ++ y) == Mod && (y = 0);
        if(!key[y]) sta[ ++ tt] = y, key[y] = x;
        return val[y];
    }
    inline void Clear()
    {
        for(int i = 1; i <= tt; i ++ ) key[sta[i]] = val[sta[i]] = 0;
        tt = 0;
    }
};
HashTable S;

int main()
{
    Map['('] = 2, Map[')'] = 3;
    Map['['] = 4, Map[']'] = 5;
    Map['{'] = 6, Map['}'] = 7;
    Map['<'] = 8, Map['>'] = 9;
    int T;
    Read(T);
    while(T -- )
    {
        Read(n), Read(m), Read(s + 1);
        for(int i = 1; i <= n; i ++ )
        {
            ql[i].clear();
            qr[i].clear();
            s[i] = Map[(int)s[i]];
        }
        sl.clear(), sr.clear(), S.Clear();
        for(int i = 1; i <= m; i ++ )
        {
            int l, r;
            Read(l), Read(r);
            ql[r].push_back(l - 1), qr[n - l + 1].push_back(n - r);
        }

        InitHash();
        Work(sl, ql), emp = 0;
        reverse(s + 1, s + n + 1);
        for(int i = 1; i <= n; i ++ ) s[i] ^= 1;
        Work(sr, qr);

        int ans = emp / 2;
        for(LL i : sl) S[i] ++ ;
        for(LL i : sr)
        {
            int &t = S[i];
            if(t) t -- , ans ++ ;
        }
        printf("%d\n", ans);
    }
    return 0;
}