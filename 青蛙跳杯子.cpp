
/*
    https://www.lanqiao.cn/problems/102/learning/
    用到了BFS和一点string相关知识
    基本上就是“九宫重排”的简化版
*/

#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <set>
using namespace std;

struct node//此题结构体只需要一维的整数x
{
    int x;
    int step;
    string st;
};

queue<node>canMove;//与“九宫重排”的思路一致
set<string>checked;

string start,endOut;
int len=0;//用len储存string的长度，此题的长度一直保持不变
void buildStartAndEnd()//同样的将空的位置设置为起点
{
    cin>>start>>endOut;
    int i=0;
    while(start[i]!='*')//找到string中*的位置
        i++;
    struct node newNode={i,0,start};//构建step为0的结构体
    canMove.push(newNode);//将起点放入队列中
    checked.insert(start);
    len=start.size();//得到string的长度
}

int dx[6]={-3,-2,-1,1,2,3};//此题的移动只能向x轴上的六个位置走

int main(void)
{
    buildStartAndEnd();
    while(!canMove.empty())//下面基本上和“九宫重排”完全一致
    {
        struct node temNode;
        temNode=canMove.front();
        canMove.pop();
        if(temNode.st==endOut)
        {
            cout<<temNode.step;
            return 0;
        }
        int tmx;
        for(int k=0;k<=5;k++)//注意此题有六种移动情况
        {
            tmx=temNode.x+dx[k];
            if(tmx>=0&&tmx<len)
            {
                string tmst;
                tmst=temNode.st;
                swap(tmst[tmx],tmst[temNode.x]);
                if(!checked.count(tmst))
                {
                    struct node newNode={tmx,temNode.step+1,tmst};
                    canMove.push(newNode);
                    checked.insert(tmst);
                }
            }
        }
    }
    cout<<"-1";
    return 0;
}
