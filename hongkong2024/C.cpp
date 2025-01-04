#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 5e5+50 , mod = 1e9+7;

LL n , m , k;
LL a[N];
void AC() {
    cin >> n ; LL mx = 0 ;
    for (int i = 1; i <= n ; i++) {
        cin >> a[i]; 
        mx = max(mx,a[i]);
    }
    for (int i = 1; i <= n ; i++) {
        if (a[i] == mx) {
            cout << i << " ";
        }
    }
    cout << '\n';
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