#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int N = 1e6+100000 , mod = 1e9+7 , P = 131;

ULL h[N] , p[N] , h1[N];

void init() {
    p[0] = 1;
    for (int i = 1; i < N ; i++) {
        p[i] = p[i-1] * P ;
    }
}

ULL get( int l , int r ) {
    return h[r] - h[l-1] *p[r-l+1];
}

ULL get1(int l , int r) {
    return h1[r]-h1[l-1]*p[r-l+1];
}

void AC() {
    string a , b ; cin >> a >> b ;
    int lena = a.size() , lenb = b.size() ;
    a = " " + a + a;
    b = " " + b ;
    map<ULL , int> mp;
    
    for (int i = 1 ; i <= lena*2; i++ ){
        h[i] = h[i-1] * P + a[i];
    }
    for (int i = 1; i+lena-1 < a.size(); i++) {
        mp[ get(i,i+lena-1) ] = 1;
    }
    for (int i = 1 ; i <= lenb ; i++ ) {
        h1[i] = h1[i-1]*P + b[i];
    }
    LL cnt = 0 ;
    for (int i = 1 ; i + lena - 1 <= lenb ; i++ ) {
        if (mp[ get1(i,i+lena-1) ]) cnt++;
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int T = 1 ;
    init();
    cin >> T ;
    while (T--) {
        AC();
    }
    return 0;
}