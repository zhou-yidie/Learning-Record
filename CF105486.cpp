#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+100 , mod = 1e9+7;
LL n ,  k ,T  ;
string s ;

void AC() {
    vector<pii> ve;
    cin >> s ; n = s.size() ;
    bool fg = true , f2 = false;
    if (s[0] != '>' || s[n-1] != '>' ||  s[n-2] != '>'||  s[n-3] != '>') {
        fg = false;
    }
    for (auto vl : s ) {
        if (vl == '-') {
            f2 = true;
        }
    }
    if (fg && f2) {

    } else {
        cout << "No\n";
        return ;
    }
    int i = n-1;
    for (i = n- 1 ; i >= 2 ; i--) {
        if (s[i] != '>') {
            break;
        }
        if (i == 2) {
            ve.push_back({1,5}) ;
        } else if ( i== 3) {
            ve.push_back({1,5}) ;
        } else {
            ve.push_back({i-3,5}) ;
        }
    }
    for (int j = 0 ; j <= i ; j ++) {
        if (s[j] == '>') {
            ve.push_back({j+1,5}) ;
        } else {
            int st = j , ed = j;
            while (ed < n && s[ed] == '-') {
                ed ++ ;
            }
            j = ed - 1;
            ve.push_back({st,ed-st+4}) ;
        }
    }
    cout << "Yes" << " " << ve.size() << '\n';
    for (auto v : ve) {
        cout << v.first << " " << v.second << '\n';
    }

}
// 0010101120011
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}

/*


5
0110101
01020102
0000021111
1012121010
0100202010


3
4
0
6
0



 */