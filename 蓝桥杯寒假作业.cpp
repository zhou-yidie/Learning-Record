#include<iostream>
using namespace std;
int a[13] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
bool vis[13];
int b[13];
int ans = 0;
void dfs(int s, int t)
{
    if (s == 13)
    {
         ans++;
        return;
    }

    if (s == 3 && b[0] + b[1] != b[2]) return;
    if (s == 6 && b[3] - b[4] != b[5]) return;
    if (s == 9 && b[6] * b[7] != b[8]) return;
    if (s == 12 && (double)b[9]*1.0/b[10] != b[11]) return;
    for (int i = 0; i < t; i++)
    {
        if (!vis[i])
        {
            vis[i] = true;
            b[s] = a[i];
            dfs(s + 1, t);
            vis[i] = false;
        }
    }
    
}
int main()
{
    dfs(0, 13);
    cout << ans;
}

//https://www.lanqiao.cn/problems/1388/learning/?page=8&first_category_id=1&sort=students_count&tags=%E7%9C%81%E8%B5%9B
