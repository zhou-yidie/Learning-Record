#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , k;

LL exgcd(LL a, LL b , LL &x, LL &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    LL x1, y1;
    LL gcd = check(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}


void AC() {
    LL a, b , c , x,  y ; cin >> a >> b >> c;
    LL gcd = exgcd(a, b, x, y);
    if (c % gcd != 0) {
        cout << "no\n";
        return ;
    } else {
        x=(c/gcd)*x;
        y=(c/gcd)*y;
        cout<<x<<" "<<y<<endl;

        
    }
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