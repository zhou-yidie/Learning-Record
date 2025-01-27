#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

string a , b , ans;


void AC() {
    cin >> a >> b;
    int n = a.size(), m = b.size(), pre = 0 , i = n - 1, j = m - 1;
    for (i = n - 1, j = m - 1; i >= 0 && j >= 0; i --, j --) {
        char c = a[i] + b[j] - '0' + pre;
        if (c > '9') {
            c -= 10;
            pre = 1;
        }
        else pre = 0;
        ans += c;
    }
    while (i >= 0) {
        char c = a[i] + pre;
        if (c > '9') {
            c -= 10;
            pre = 1;
        }
        else pre = 0;
        ans += c;
        i --; 
    }
    while (j >= 0) {
        char c = b[j] + pre;
        if (c > '9') {
            c -= 10;
            pre = 1;
        }
        else pre = 0;
        ans += c;
        j --; 
    }
    if (pre) ans += '1';
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
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