#include <iostream>
#include<queue>
using namespace std;
int n, m,a[501][501]{},vis[502][502];
int dx[4]{ 0,0,1,-1 };
int dy[4]{ 1,-1,0,0 };
long long time1 = 0;

//每个格子的属性为x,y,time.   time意为在time1==time时染色完成    其中this->time=time1+a[x][y] (染色时间加当前时间) 
struct ge {

    int x, y, time;
    ge(int xx, int yy, int tt) :x(xx), y(yy), time(tt) {};//构造函数
    bool operator> (const ge& other)const {//重载>运算符，改为按时间增序排列
        return time > other.time;
    }
};

priority_queue <ge,vector<ge>,greater< ge > > q;//按自定义顺序排列的优先队列

int main() {
    //输入每个格子的染色时间，用a[n][m]存储
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 0; i <= 501; i++)//设置边界不可访问
    {
        vis[0][i] = 1;
        vis[i][0] = 1;
        vis[n + 1][i] = 1;
        vis[i][m + 1] = 1;
    }

    //按题目要求，将格子(1,1)染色
    vis[1][1] = 1;
    q.push(ge(1, 1, a[1][1]));

    time1 = a[1][1];//time1时间更新为格子(1,1)染色完成后

    //将上下左右四个方向未被染色的格子染色并加入队列
    for (int i = 0; i < 4; i++)
        if (!vis[q.top().x + dx[i]][q.top().y + dy[i]])//如果没被染色过
        {            q.push(ge(q.top().x + dx[i], q.top().y + dy[i], a[q.top().x + dx[i]][q.top().y + dy[i]] + time1));
                    vis[q.top().x + dx[i]][q.top().y + dy[i]] = 1;
        }
    q.pop();//染色完成后移出队列

    //重复上述过程直到q为空，此时代表全部染色完成
    while (!q.empty())
    {
        time1 = q.top().time;//time1时间更新为q.top()格子染色完成后
        for (int i = 0; i < 4; i++)
            if (!vis[q.top().x + dx[i]][q.top().y + dy[i]])
            {            q.push(ge(q.top().x + dx[i], q.top().y + dy[i], a[q.top().x + dx[i]][q.top().y + dy[i]] + time1));
                        vis[q.top().x + dx[i]][q.top().y + dy[i]] = 1;
            }
        q.pop();
    }

    cout << time1;
    return 0;
}
