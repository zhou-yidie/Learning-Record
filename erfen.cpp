#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+10;
int n , m , l[N], r[N];

int main() {
    cin >> n ; 
    for (int i = 0; i < n; i ++ ) cin >> l[i] >> r[i];
    sort(l, l + n);
    sort(r, r + n);

    int q = n * (n-1) / 2;
    for (int i = 0 , j= 0 ; i < q; i ++ ) {
        while (j < n && r[j] < l[i]) j ++ ;
        cout << " i = " << i << " j = " << j << '\n';
        q -= j ;
    }
    cout << q << '\n';
}
