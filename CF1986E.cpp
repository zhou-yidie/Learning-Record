#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , q , k ,ans ;
LL a[N] , l[N] , r[N]  ;
map<LL, vector<LL> > mp ;
void AC() {
    cin >> n >> k ;
    mp.clear() ;
    for (int i = 1; i <= n ; i++ ) {
        cin >> q ;
        mp[ (q%k) ].push_back(q) ;
    }
    bool ji = false , fg = false ;
    ans= 0 ;
    for (auto tmp : mp) {
        sort(tmp.second.begin() , tmp.second.end()) ;

        int sz = tmp.second.size() ;
        //cout << tmp.first << " " << sz << '\n';
        if (sz & 1) {
            if ( n & 1) {
                if (!ji) { ji = true ; }
                else {
                    fg = true ;
                    break;
                }
            } else {
                fg = true ;
                break;
            }
        }
        LL sum1 = 0  ;
        for (int j = 0 ; j + 1 < sz ; j += 2 ) {
            sum1 += ( tmp.second[j+1] - tmp.second[j] ) / k ;
        }

        if (sz & 1) {
            LL mn = LONG_LONG_MAX ;
            a[0] = l[1]  = r[sz-1] = 0 ;
            for (int j = 1 ; j < sz ; j ++ ) {
                a[j] = (tmp.second[j] - tmp.second[j-1]) / k ;
            }
            for (int j = 1 ; j <= sz-1 ; j+=2) {
                if (j == 1) l[j] = a[j] ;
                else l[j] = l[j-2] + a[j] ;
            }
            for (int j = sz - 1; j >= 1 ; j -= 2) {
                if (j == sz - 1) r[j] = a[j] ;
                else r[j] = r[j+2] + a[j] ;
            }
            for (int j = 1 ; j < sz ; j++ ) {
                LL tp = 0 ;
                if (j & 1) {
                    if (j != 1) tp += l[j-2] ;
                    tp += r[j+1] ;
                } else {
                    tp += l[j-1] ;
                    if (j != sz - 1) tp += r[j+2] ;
                }
                mn = min(mn , tp) ;
            }
            if (sz == 1) {
                mn = 0 ;
            }
            //mn = min({mn,sum1,sum2}) ;
            ans += mn ;
        } else {
            ans += sum1;
        }



    }
    if (fg) cout << "-1\n";
    else cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int T = 1 ;
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}