#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+100 , mod = 1e9+7;
LL n ,  k ,T  ;
string s ;

void AC() {
    cin >> s ;
    s = " " + s ;
    vector<int> hou , ed , er ;
    for (int i = 1 ; i < (int)s.size() ; i++ ) {
        if (s[i] == '2') {
            hou.push_back(2);
        } else if (s[i] == '1') {
            if (hou.size() == 0) {
                hou.push_back(1);
            } else {
                auto pre = hou[ hou.size() - 1 ] , now = s[i]-'0' ;
                if (pre == now) {
                    hou.pop_back() ;
                } else {
                    hou.push_back(1);
                }
            }
        } else {
            if (hou.size() == 0) {
                hou.push_back(0);
            } else {
                auto pre = hou[ hou.size() - 1 ] , now = s[i]-'0' ;
                if (pre == now) {
                    hou.pop_back() ;
                } else {
                    hou.push_back(0);
                }
            }
        }
    }

    int sz = hou.size();
    for (int i = 0 ; i < sz ; i++ ) {
        if (i & 1) {
            if (hou[i] == 0)  {
                hou[i] = 1-hou[i];
            } else if (hou[i] == 1) {
                hou[i] = 1-hou[i];
            }
        }
    }
    int z_num =0 ,one_num = 0 , er_num = 0;
    for (auto v : hou) {
        if (v == 0) z_num ++ ;
        if (v == 1) one_num ++ ;
        if (v == 2) er_num ++ ;
    }
    LL cha = abs(z_num - one_num) ;
    if (cha >= er_num) {
        cout << cha-er_num<< '\n';
    } else {
        if ((cha + er_num) & 1) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
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