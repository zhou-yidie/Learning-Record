#include <iostream>
#include<algorithm>
using namespace std;
int main()
{
    int a[100005], b[100005], c[100005];
    long long n = 0, ans = 0;
    long long i = 0, s1 = 0, s2 = 0;
    cin >> n;
    for (i = 0; i < n; i++) cin >> a[i];
    for (i = 0; i < n; i++) cin >> b[i];
    for (i = 0; i < n; i++) cin >> c[i];
    sort(a, a + n); sort(b, b + n); sort(c, c + n);

    for (i = 0; i < n; i++)
    {
        //s1 = 0; s2 = 0;
        while (s1 < n && a[s1] < b[i]) s1++;
        while (s2 < n && c[s2] <= b[i]) s2++;
        ans += ((long long)s1 * (n - s2));
    }
    cout << ans << endl;
    return 0;
}
