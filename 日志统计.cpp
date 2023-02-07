////尺取法（同向扫描） - 日志统计
#include<bits/stdc++.h>
using namespace std;

const int N = 100005;
struct Node
{
    int id;
    int ts;
}a[N];          //存储日志信息
bool rt[N];     //热帖标记 - 如果第id个帖子为热帖，则将rt[id]置为1
int n,d,k;

bool maps(Node x,Node y)
{
    if(x.id == y.id)
    {
        return x.ts < y.ts;
    }
    return x.id < y.id;
}

int main()
{
    //读取日志
    cin >> n >> d >> k;
    for(int i = 0;i < n;i++)
    {
        cin >> a[i].ts >> a[i].id;
    }
    //排序 - 先按店铺升序，再按时间升序
    sort(a ,a + n,maps);
    //记录最大id - 以便后面检查热帖输出id
    int id_max = a[n - 1].id;     
    //正向扫描处理日志
    int i = 0;
    int j = 0;
    while(j < n)
    {
        //判断两个指针是否在同一家店铺 - 不是则更新i指针
        if(a[i].id != a[j].id)
        {
            i = j;
        }
        //在规定时间段内 - 判断是否符合热帖要求
        if(a[j].ts - a[i].ts <= d)
        {
            //点赞数量达到热帖要求 - 标记为热帖
            if(j - i + 1 >= k)
            {
                rt[a[j].id] = 1;
            }
        }
        //超过了规定时间 - 缩小时间范围
        else
        {
            i++;            //移动i指针
            continue;
        }
        j++;                //更新j指针
    }
    //遍历热帖标记数组，数组大小是N(最大id值) = 100000;(注意不是输入的n(日志数量))
    //或者，可以在输入的时候就记录下最大id的值，这里遍历就不用做多余的遍历
    for(int i = 0;i <= id_max/*i < N*/;i++)
    {
        if(rt[i] == 1)
        {
            cout << i << endl;
        }
    }
    return 0;
}
