#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5 ;

typedef long long LL ;
deque<int> dq;
int n , st[N] ; string s;
LL ans , tot;


void AC() {
    cin >> n >> s ;
    tot = ans = 0 ;
    for (int i = 0 ; i < n ; i++) {
        if (s[i] == '1') {
            dq.push_back(i+1) ;
        } else {
            st[++tot] = i + 1;
        }
        ans += i+1;
    }
    while (!dq.empty()) {
        auto x = dq.back();dq.pop_back();
        while (tot && st[tot] > x) tot--;
        if (tot) {
            tot--;
            ans -= x;
        } else {
            if (!dq.empty() ) {
                dq.pop_front();
                ans -= x ;
            }
         }
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int T = 1; 
    cin >> T ;
    while (T--) {
        AC();
    }
}