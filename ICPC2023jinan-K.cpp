

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

constexpr int N = 500010;

mt19937 rnd(114514);
int a[N];
int n, root, T1, T2, T3, idx;
LL k;
struct FHQ
{
    int ls, rs, val, key, sz;
    LL s;
} fhq[N];

int create(int v)
{
    fhq[ ++ idx] = {0, 0, v, (int)rnd(), 1, v};
    return idx;
}

void pushup(int u)
{
    fhq[u].sz = fhq[fhq[u].ls].sz + fhq[fhq[u].rs].sz + 1;
    fhq[u].s = fhq[fhq[u].ls].s + fhq[fhq[u].rs].s + fhq[u].val;
}

void split(int u, int v, int &x, int &y)
{
    if (!u)
    {
        x = 0, y = 0;
        return;
    }

    if (fhq[u].val > v)
    {
        y = u;
        split(fhq[u].ls, v, x, fhq[u].ls);
    }
    else
    {
        x = u;
        split(fhq[u].rs, v, fhq[u].rs, y);
    }

    pushup(u);
}

int merge(int x, int y)
{
    if (!x || !y) return x + y;
    if (fhq[x].key > fhq[y].key)
    {
        fhq[x].rs = merge(fhq[x].rs, y);
        pushup(x);
        return x;
    }
    else
    {
        fhq[y].ls = merge(x, fhq[y].ls);
        pushup(y);
        return y;
    }
}

void insert(int x)
{
    split(root, x, T1, T2);
    root = merge(merge(T1, create(x)), T2);
}

void erase(int x)
{
    split(root, x - 1, T1, T2);
    split(T2, x, T2, T3);
    T2 = merge(fhq[T2].ls, fhq[T2].rs);
    root = merge(merge(T1, T2), T3);
}

int kth(int k)
{
    int u = root;
    while (u)
    {
        int tmp = fhq[fhq[u].ls].sz + 1;
        if (k == tmp) break;
        else if (k < tmp) u = fhq[u].ls;
        else
        {
            k -= tmp;
            u = fhq[u].rs;
        }
    }

    return fhq[u].val;
}

LL calc(int len)
{
    int median = kth(len / 2 + 1);
    split(root, median, T1, T2);
    LL res = 1LL * median * fhq[T1].sz - fhq[T1].s + fhq[T2].s - 1LL * median * fhq[T2].sz;
    root = merge(T1, T2);
    return res;
}

void solve()
{
    root = T1 = T2 = T3 = idx = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; i ++ ) cin >> a[i], a[i] -= i;

    insert(a[1]);
    int res = 0;
    for (int i = 1, j = 1; i <= n; i ++ )
    {
        while (j + 1 <= n && calc(j - i + 1) <= k)
        {
            j ++ ;
            insert(a[j]);
        }

        if (calc(j - i + 1) <= k) res = max(res, j - i + 1);
        else res = max(res, j - i);
        erase(a[i]);
    }

    cout << res << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T -- ) solve();

    return 0;
}
