#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e6 + 10;

int  n,a[N];
vector<pair<int,int> > ans;


void AC() {
    cin >> n ;
    ans.clear();
    set<int> st[3];
    for (int i = 1; i <= n ; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            st[0].insert(i);
        } else if (a[i] == 1) {
            st[1].insert(i);
        } else {
            st[2].insert(i);
        }
    }

    int zero_num = st[0].size(), one_num = st[1].size();
    for (int i = 1; i <= zero_num; i++) {
        if (a[i] == 1) {
            int nxt = *st[0].rbegin();
            ans.push_back({i,nxt});
            swap(a[i],a[nxt]);
            st[0].erase(nxt);
            st[0].insert(i);
            st[1].erase(i);
            st[1].insert(nxt);
        } else if (a[i] == 2) {
            int nxt = *st[1].rbegin();
            ans.push_back({i,nxt});
            swap(a[i],a[nxt]);
            st[1].erase(nxt);
            st[1].insert(i);
            st[2].erase(i);
            st[2].insert(nxt);
            nxt = *st[0].rbegin();
            ans.push_back({i,nxt});
            swap(a[i],a[nxt]);
            st[0].erase(nxt);
            st[0].insert(i);
            st[1].erase(i);
            st[1].insert(nxt);
        }
    }

    for (int i = zero_num + 1; i <= zero_num+one_num; i++) {
        if (a[i] == 2) {
            int nxt  = *st[1].rbegin();
            ans.push_back({i,nxt});
            swap(a[i], a[nxt]);
            st[1].erase(nxt);
            st[1].insert(i);
            st[2].erase(i);
            st[2].insert(nxt);
        }
    }

    // for (int i = 1; i <= n ; i++) {
    //     cout << a[i] << " ";
    // }
    // cout << '\n';
    cout <<    ans.size() << '\n';
    for (auto v : ans) {
        cout << v.first << " " << v.second << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    cin >> _;
    while (_--) {
       AC(); 
    }
    return 0;
}
