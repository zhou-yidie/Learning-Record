#include<bits/stdc++.h>
using namespace std;
typedef long long LL ;
typedef pair<int,int> pii;
const int N = 2e5+50 , mod = 1e9+7;

LL n , m , k;
string s , t ;
map<char,int> target, window;
map<char, bool> pp;

void AC() {
    cin >> s >> t ;
    LL n = s.size(), m = t.size();
    // 如果 s 的长度小于 t 的长度，直接返回空字符串
    if (m > n) {
        cout << "\"\"";
        return;
    }
    // 如果 s 和 t 相等，直接返回 s
    if (s == t) {
        cout << s << '\n';
        return;
    }
    // 记录 t 中每个字符的出现次数，并标记该字符在 t 中出现过
    for (auto v : t) {
        target[v]++;
        pp[v] = true;
    }
    LL left = 0, right = 0;
    int valid = 0;
    LL min_len = 1e18, start = -1;
    // 右指针移动，扩大窗口
    while (right < n) {
        char c = s[right++];
        // 如果当前字符在 t 中出现过
        if (pp[c]) {
            window[c]++;
            // 如果当前字符在窗口中的出现次数等于在 t 中的出现次数，满足条件的字符种类数加 1
            if (window[c] == target[c]) valid++;
        }
        // 当满足条件的字符种类数等于 t 中不同字符的种类数时，尝试缩小窗口
        while (valid == target.size()) {
            // 更新最小子串的长度和起始位置
            if (right - left < min_len) {
                min_len = right - left;
                start = left;
            }
            char d = s[left++];
            // 如果左指针指向的字符在 t 中出现过
            if (pp[d]) {
                // 如果该字符在窗口中的出现次数等于在 t 中的出现次数，满足条件的字符种类数减 1
                if (window[d] == target[d]) valid--;
                window[d]--;
            }
        }
    }
    // 如果没有找到满足条件的子串，返回空字符串
    if (start == -1) cout << "\"\"";
    else cout << s.substr(start, min_len) << '\n';
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