#include<iostream>
#include<cstdio>
#include<cmath>
 
using namespace std;
 
int exgcd(int a,int b,int &x,int &y)//扩展欧几里得算法
{
    if(b==0)
    {
        x=1;y=0;
        return a;  //到达递归边界开始向上一层返回
    }
    int r=exgcd(b,a%b,x,y);
    int temp=y;    //把x y变成上一层的
    y=x-(a/b)*y;
    x=temp;
    return r;     //得到a b的最大公因数
}


signed main()
{
	int a = 6,b = 9;
	int x,y;
	cout << exgcd(a,b,x,y) << endl;
	a = 12, b = 8;
	cout << exgcd(a,b,x,y) << endl;
	a = 105, b = 240;
	cout << exgcd(a,b,x,y) << endl;
	
	return 0;
} //https://blog.csdn.net/destiny1507/article/details/81750874?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168310985616800186537178%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=168310985616800186537178&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~hot_rank-1-81750874-null-null.142^v86^wechat,239^v2^insert_chatgpt&utm_term=%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95&spm=1018.2226.3001.4187
