#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , k , ans;
LL a[30] , s[30];

void dfs(int id , int sum) {
    if (id == n+1) {
        if (sum == k) {
            ans++;
        }
        return ;
    }
    dfs(id + 1, sum + a[id]);
    dfs(id + 1, sum-a[id]);
}

void AC() {
    cin >> n ;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    sort(a + 1, a + 1 + n , greater<int>());
    for (int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + a[i];
    ans = 0;
    cin >> k;
    dfs(1,0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int T = 1 ;
    //cin >> T ;
    while (T--) {
         AC();
    }
    return 0;
}