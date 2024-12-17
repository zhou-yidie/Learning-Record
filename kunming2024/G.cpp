#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL a , b ,ans;

void AC() {
    cin >> a >> b ; ans = 50;
    queue< array<LL , 3> > qu;
    qu.push({a,b,0});
    while (!qu.empty()) {
        auto [xx,yy,cnt] = qu.front(); qu.pop();
        if (cnt >= ans) { continue; }
        if (xx == 0 && yy == 0) {
            ans = cnt; 
        } else if ( xx == 0 || yy == 0 ) {
            ans = cnt + 1;
        } else {
            LL nxa = xx - __gcd(xx,yy) , nxb = yy - __gcd(xx,yy);
            
            qu.push({xx,nxb,cnt+1});
            qu.push({nxa,yy,cnt+1});
        }
    }
    cout << ans << "\n";
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