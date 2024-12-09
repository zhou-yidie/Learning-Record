#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 1e6+50 , mod = 1e9+7;

LL n , m ;
LL a[N] , b[N];
void AC() {
    cin >> n >> m ;
    for (int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for (int i = 1; i  <= m ; i ++ ) {
        cin >> b[i];
    }
    int aid = 1 , bid = 1 ;
    while (bid <= m && aid <= n) {
        if (b[bid] == a[aid]) {
            aid++;bid++;
        } else {
            aid++;
        }
    }
    if (bid != m +1) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
    }
    return ;
    // today,xiyousuanfajiaoliuqun naomale
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}