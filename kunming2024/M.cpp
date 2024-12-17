#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

int mp[1010][1010];

void AC() {
    int n, m ; cin >> n >> m ;
    int cnt = 0;
    for (int i = 1; i  <= n + m ; i ++) {
        int j = 1 , ii = i ;
        while (ii >= 1) {
            if (ii >= 1 && ii <= n  && j >= 1 && j <= m) {
                mp[ii][j] = ++ cnt;
            }
            ii -- ; j ++ ;
        }
    }
    cout << "yes\n";
    for (int i = 1; i <= n ; i ++) {
        for (int j = 1; j <= m ; j ++) {
            cout << mp[i][j] << " ";
        }
        cout << "\n";
    }
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