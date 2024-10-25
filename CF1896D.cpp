#include <bits/stdc++.h>
using namespace std;
int t, n, q, a[200005], c[200005], s1[200005], s2[200005];
set<int> pos;
set<int>::iterator pl, pr;
void add(int x, int k) {
    while (x <= n) {
        c[x] += k;
        x += (x & -x);
    }
}
int query(int x) {
    int ret = 0;

    while (x) {
        ret += c[x];
        x -= (x & -x);
    }

    return ret;
}
bool check(int x) {
    int sum1 = query(n), sum2;

    if (x <= sum1 && x % 2 == sum1 % 2)
        return 1;

    pl = pos.begin(), pr = pos.end();

    if (!pos.size())
        return 0;

    sum2 = query(n) - query((*pl));
    pr--, sum2 = max(sum2, query((*pr) - 1));
    return x <= sum2 && x % 2 == sum2 % 2;
}
int main() {
    cin >> t;

    while (t--) {
        for (int i = 0; i <= n + 1; i++)
            c[i] = 0;

        cin >> n >> q;
        pos.clear();

        for (int i = 1; i <= n; i++) {
            cin >> a[i], add(i, a[i]);
            s1[i] = s1[i - 1] + a[i];
            s2[i] = s2[i + 1] + a[i];

            if (a[i] == 1)
                pos.insert(i);
        }

        while (q--) {
            int op, x, k;
            cin >> op >> x;

            if (op == 1) {
                if (check(x))
                    puts("YES");
                else
                    puts("NO");
            } else {
                cin >> k;

                if (a[x] == 1)
                    pos.erase(x);

                add(x, -a[x]), a[x] = k, add(x, a[x]);

                if (a[x] == 1)
                    pos.insert(x);
            }
        }
    }

    return 0;
}
