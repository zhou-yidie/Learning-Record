#include<bits/stdc++.h>
using namespace std;

int mp[200][200], row = 0, col = 0, cnt = 1;

int main() {
    mp[0][0] = 1;
    while(!mp[19][19]) {
        //右移
        mp[row][++col] = ++cnt;
        //左下方
        while(col) {
            mp[++row][--col] = ++cnt;
        }
        //下移
        mp[++row][col] = ++cnt;
        //右上方
        while(row) {
            mp[--row][++col] = ++cnt;
        }
    }
    /*for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            cout << mp[i][j] << "  ";
        }
        cout << endl;
    }*/
    cout << mp[19][19];
    return 0;
}
