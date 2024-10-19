#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int, int>
#define endl "\n"

using point_t=long long;  //全局数据类型，可修改为 long long 等

constexpr point_t eps=1e-8;
constexpr long double PI=3.1415926535897932384l;

// 点与向量
template<typename T> struct point
{
    T x,y;

    bool operator==(const point &a) const {return (abs(x-a.x)<=eps && abs(y-a.y)<=eps);}
    bool operator<(const point &a) const {if (abs(x-a.x)<=eps) return y<a.y-eps; return x<a.x-eps;}
    bool operator>(const point &a) const {return !(*this<a || *this==a);}
    point operator+(const point &a) const {return {x+a.x,y+a.y};}
    point operator-(const point &a) const {return {x-a.x,y-a.y};}
    point operator-() const {return {-x,-y};}
    point operator*(const T k) const {return {k*x,k*y};}
    point operator/(const T k) const {return {x/k,y/k};}
    T operator*(const point &a) const {return x*a.x+y*a.y;}  // 点积
    T operator^(const point &a) const {return x*a.y-y*a.x;}  // 叉积，注意优先级
    int toleft(const point &a) const {const auto t=(*this)^a; return (t>eps)-(t<-eps);}  // to-left 测试
    T len2() const {return (*this)*(*this);}  // 向量长度的平方
    T dis2(const point &a) const {return (a-(*this)).len2();}  // 两点距离的平方

    // 涉及浮点数
    long double len() const {return sqrtl(len2());}  // 向量长度
    long double dis(const point &a) const {return sqrtl(dis2(a));}  // 两点距离
    long double ang(const point &a) const {return acosl(max(-1.0l,min(1.0l,((*this)*a)/(len()*a.len()))));}  // 向量夹角
    point rot(const long double rad) const {return {x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad)};}  // 逆时针旋转（给定角度）
    point rot(const long double cosr,const long double sinr) const {return {x*cosr-y*sinr,x*sinr+y*cosr};}  // 逆时针旋转（给定角度的正弦与余弦）
};

using Point=point<point_t>;

void solve()
{
    int n;
    cin >> n;
    Point o;
    int x, y, r;
    cin >> x >> y >> r;
    o = {(point_t)x, (point_t)y};
    vector<Point> a(n);
    for (int i = 0; i < n; i ++ ) {
        cin >> x >> y;
        a[i] = {(point_t)x, (point_t)y};
    }
    point_t ans = 0, now = 0;
    for (int i = 0, j = 1; i < n; i ++ ) {
        while(1) {
            int net_j = (j + 1) % n;
            point_t cross = ((a[net_j] - a[i]) ^ (o - a[i]));
            if (cross <= 0 || (__int128_t)cross * cross < (__int128_t)r * r * a[i].dis2(a[net_j])) {
                break;
            }
            cross = (a[j] - a[i]) ^ (a[net_j] - a[i]);
            now += abs(cross);
            j = net_j;
        }
        ans = max(ans, now);
        int net_i = (i + 1) % n;
        point_t cross = (a[j] - a[i]) ^ (a[net_i] - a[i]);
        now -= abs(cross);
    }
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T --)
        solve();
}
