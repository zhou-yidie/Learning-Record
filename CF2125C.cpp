#include <bits/stdc++.h>
using namespace std;
vector<int> one, two,three,four;

void init() {
    one.push_back(2);one.push_back(3);one.push_back(5);one.push_back(7);
    two.push_back(6);two.push_back(10);two.push_back(14);two.push_back(15);two.push_back(21);two.push_back(35);
    three.push_back(30);three.push_back(105);three.push_back(70);three.push_back(42);
    four.push_back(210);
}

long long haoNum(long long x){
    long long res = x;
    for (int i = 0; i < one.size(); i++) {
        res -= x / one[i];
    }
    for (int i = 0; i < two.size(); i++) {
        res += x / two[i];
    }
    for (int i = 0; i < three.size(); i++) {
        res -= x / three[i];
    }
    for (int i = 0; i < four.size(); i++) {
        res += x / four[i];
    }
    return res;
}

void AC() {
    long long l,r; cin >> l >> r;
    cout << haoNum(r) - haoNum(l-1) << '\n';
}
int main() {
    int T;
    cin >> T;
    init();
    while (T--) {
        AC();
    }
    return 0;
}