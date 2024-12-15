#include <iostream>
using namespace std;
typedef long long ll;
const int N = 2e5 + 3;
const int INF = 1e9;
namespace SegmentTree
{
    struct node
    {
        int l, r, num;
        ll sum;
    } st[N << 5];
    int tot;
    void update(int &id, int segl, int segr, int pos, int val)
    {
        if (!id)
            id = ++tot;
        st[id].num += val;
        st[id].sum += val * pos;
        if (segl == segr)
            return;
        int mid = (segl + segr) >> 1;
        if (pos <= mid)
            update(st[id].l, segl, mid, pos, val);
        else
            update(st[id].r, mid + 1, segr, pos, val);
    }
    int query(int id, int segl, int segr, ll sum)
    {
        if (segl == segr)
            return (sum<=0?0:(sum+segl-1)/segl);
        int mid = (segl + segr) >> 1;
        if (st[st[id].r].sum >= sum)
            return query(st[id].r, mid + 1, segr, sum);
        return query(st[id].l, segl, mid, sum - st[st[id].r].sum) + st[st[id].r].num;
    }
};
int a[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, T, rt = 0, cnt = 0;
    ll sum = 0;
    cin >> n >> T;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        if (a[i] > 0)
            SegmentTree::update(rt, 1, INF, a[i], 1), ++cnt;
        sum += a[i];
    }
    for (int kase = 1; kase <= T; ++kase)
    {
        int x, v;
        cin >> x >> v;
        if (a[x] > 0)
            SegmentTree::update(rt, 1, INF, a[x], -1), --cnt;
        if (v > 0)
            SegmentTree::update(rt, 1, INF, v, 1), ++cnt;
        sum = sum - a[x] + v;
        a[x] = v;
        cout << cnt - SegmentTree::query(1, 1, INF, sum) +1<< "\n";
    }
    return 0;
}
