#include <bits/stdc++.h>
using namespace std;
void AC() {
    string s; cin >> s;
    string ans = "";
    int FNum = 0, TNum = 0, NNum = 0;
    for (char c : s) {
        if (c == 'F') {
            FNum++;
        } else if (c == 'T') {
            TNum++;
        } else if (c == 'N') {
            NNum++;
        } else {
            ans += c;
        }
    }
    for (int i = 0; i < TNum; i++) {
        ans += 'T';
    }
    for (int i = 0; i < FNum; i++) {
        ans += 'F';
    }
    for (int i = 0; i < NNum; i++) {
        ans += 'N';
    }
    cout << ans << '\n';
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        AC();
    }
    return 0;
}