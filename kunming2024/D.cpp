#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5, inf = 1e9;
int a[N], dp[N], tp[N], f[N], g[N], n;
int mn[22][N], mx[22][N], lg[N];
int qmn(int l, int r)
{
	int k = lg[r - l + 1];
	return min(mn[k][l], mn[k][r - (1 << k) + 1]);
}
int qmx(int l, int r)
{
	int k = lg[r - l + 1];
	return max(mx[k][l], mx[k][r - (1 << k) + 1]);
}
int pmn(int x, int y)
{
	int l = x, r = n, mid;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(qmn(x, mid) >= y)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return r;
}
int pmx(int x, int y)
{
	int l = x, r = n, mid;
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(qmx(x, mid) <= y)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return r;
}
int tag[N * 4];
pair<int, int> mnv[N * 4];
void push_up(int p)
{
	mnv[p] = min(mnv[p << 1], mnv[p << 1 | 1]);
	mnv[p].first += tag[p];
}
void build(int p, int l, int r)
{
	int mid = (l + r) >> 1;
	tag[p] = 0;
	mnv[p] = make_pair(0, l);
	if(l == r)
		return ;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void upd(int p, int l, int r, int ql, int qr, int k)
{
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr)
	{
		tag[p] += k;
		mnv[p].first += k;
		return ;
	}
	if(ql <= mid)
		upd(p << 1, l, mid, ql, qr, k);
	if(qr > mid)
		upd(p << 1 | 1, mid + 1, r, ql, qr, k);
	push_up(p);
}
pair<int, int> qry(int p, int l, int r, int ql, int qr)
{
	int mid = (l + r) >> 1;
	if(ql <= l && r <= qr)
		return mnv[p];
	pair<int, int> ans = make_pair(inf, inf);
	if(ql <= mid)
		ans = min(ans, qry(p << 1, l, mid, ql, qr));
	if(qr > mid)
		ans = min(ans, qry(p << 1 | 1, mid + 1, r, ql, qr));
	ans.first += tag[p];
	return ans;
}
vector<int> pos[2];

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int T, i, j, p, r;
	n = 1e6;
	for(i = 2; i <= n; i++)
		lg[i] = lg[i >> 1] + 1;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			scanf("%d", a + i);
		for(i = 1; i <= n; i++)
			mn[0][i] = mx[0][i] = a[i];
		for(j = 1; j <= lg[n]; j++)
			for(i = 1; i <= n - (1 << j) + 1; i++)
			{
				mn[j][i] = min(mn[j - 1][i], mn[j - 1][i + (1 << (j - 1))]);
				mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
			}
		build(1, 1, n + 1);
		g[n] = n + 1;
		f[n] = n;
		pos[0].clear();
		pos[1].clear();
		for(i = n - 1; i >= 1; i--)
		{
			tp[i] = (a[i] > a[i + 1]);
			if(tp[i])
			{
				r = pmx(i, a[i]);
				f[i] = r;
				while(!pos[0].empty() && pos[0].back() < r)
				{
					p = pos[0].back();
					pos[0].pop_back();
					if(p < f[p])
						upd(1, 1, n + 1, p + 1, f[p], -1);
					f[p] = p;
				}
				p = pmn(r + 1, a[i]);
				if(p < f[r])
				{
					upd(1, 1, n + 1, p + 1, f[r], -1);
					f[r] = p;
				}
			}
			else
			{
				r = pmn(i, a[i]);
				f[i] = r;
				while(!pos[1].empty() && pos[1].back() < r)
				{
					p = pos[1].back();
					pos[1].pop_back();
					if(p < f[p])
						upd(1, 1, n + 1, p + 1, f[p], -1);
					f[p] = p;
				}
				p = pmx(r + 1, a[i]);
				if(p < f[r])
				{
					upd(1, 1, n + 1, p + 1, f[r], -1);
					f[r] = p;
				}
			}
			pos[tp[i]].emplace_back(i);
			upd(1, 1, n + 1, i + 1, f[i], 1);
			g[i] = min(g[i + 1], qry(1, 1, n + 1, i + 1, n + 1).second);
		}
		p = n;
		i = 1;
		while(i <= n)
		{
			--p;
			i = g[i];
		}
		printf("%d\n", p);
	}
	return 0;
}