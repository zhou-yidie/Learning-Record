#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 1e6+50 , mod = 1e9+7;

LL n , m ;
LL a[N] , b[N];
void AC() {
    //cin >> n >> m ;
    for (int ii = 1 ; ii <= 10 ; ii++) {
        for (int jj = ii ; jj<= 10 ; jj++) {
            n = ii ; m = jj ;
            for (int i = 1 ; i <= n ; i ++ ) {
                a[i] = (i-1)*m + 1 ;
            }
            for (int i = 1 ; i <= m ; i++) {
                b[i] = (i-1) * n + 1;
            }
            set<int> st;
            for (int i = 1 ; i <= n ; i++ ) {
                for (int j = 1 ; j <= m ; j++) {
                    LL tmp = ( a[i] * b[j] ) % (n*m) ;
                    st.insert(tmp);
                }
            }
            cout << st.size() << " " << " n = " << n << " m = " << m << " ";
            if (st.size() == n*m ) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }
    
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