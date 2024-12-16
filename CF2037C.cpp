#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m ;
LL ans[N] ;
bool vis[N];

int sushu(int n)
{
    int i;
    if(n==1)
        return 0;
    for(i=2;i*i<=n;i++)
    {
        if(n%i==0)
            return 0;
    }
    return 1;
}

void AC() {
    cin >> n ;
    bool fg = false;
    int a = 0 , b = 0 ; 
    for (int i = 1;  i <= n ; i++) {
        ans[i] = 0; vis[i] = false;
    }
    for (int i = 3 ; i <= 2*n-1 ; i+=2) {
        if (sushu(i) == 0) {
            a = i / 2 , b = i - a ;
            vis[a] = true; vis[b] = true;
            fg = true;
            break;
        }
    }
    if (!fg) {
        cout << "-1\n";
        return ;
    }
    //cout << "a = " << a << " b = " << b << "\n";
    for (int i = 1 ; i <= n ; i+=2) {
        if (!vis[i]) {
            cout << i << ' ' ;
        }
    }
    if (a & 1){
        cout << a << " " << b << " ";
    } else {
        cout << b << " " << a << " ";
    }
    for (int i = 2 ; i <= n ; i+=2) {
        if (!vis[i]) {
            cout << i << ' ' ;
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