#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 5e5+50 , mod = 1e9+7;

LL n , m , k;
string s , t ;
int nxt[N];

void AC() {
    cin >> s >> n ;
    int nxL = s.size(),nxR = s.size();
    for (int i = s.size()-1; i >= 0; i--) {
        if (s[i] == 'L') {
            nxt[i] = nxR;
            nxL = i;
        } else {
            nxt[i] = nxL;
            nxR = i;
        }
    }
    for (int i = 1 ; i <= n; i ++) {
        cin >> t ;
        bool fg = true;
        int id = 0 , j = 0;
        if (s[0] == 'L' && t[0] != 'L') {
            fg = false;
        }
        if (s[s.size()-1] == 'R' && t[t.size()-1] != 'R') {
            fg = false;
        }
        for (j = 0; j < t.size() && fg && id < s.size();) {
            if (s[id] == t[j]) {
                id ++; j ++;
            } else {
                id = nxt[id];
            }
        }
        if (j < t.size()) {
            fg = false;
        }
        if(fg) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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