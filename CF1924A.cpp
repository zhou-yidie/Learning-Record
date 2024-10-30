#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , q , k ,ans , tar , cnt ;
char c;
bool pos[26];
string tmp;
void AC() {
    cin >> n >> m >> k ; tar = cnt = 0 ; tmp = "";
    memset(pos , 0 , sizeof (pos));
    while (k--) {
        cin >> c ;
        cnt += ( !pos[c-'a'] && c - 'a' < m ) ;
        pos[ c-'a'] = 1;
        if (cnt == m) {
            cnt = 0 ; tar++; tmp += c;
            memset(pos , 0 , sizeof (pos));
        }
    }
    if (tar >= n) {
        cout << "YES\n";
    } else {
        while (tar < n - 1) {
            tmp += 'a' ; tar++;
        }
        for (int i = 0 ; ; i++) {
            if (!pos[i]) {
                tmp += (char)(i+'a');
                break;
            }
        }
        cout << "NO\n" << tmp << '\n';
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