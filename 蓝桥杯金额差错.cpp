#include <iostream>
using namespace std;

 //初始化，[]里边的数代表金额，total[i]不为0则代表这个金额在记账本中是存在的，这样也减少了排序的过程
int total[1001]={0};
int lastm[1001]; //最后缺少的账单个数

void dfs(int mny,int bm,int num) //mny代表缺少的金额，bm代表金额开始的最小起点，num代表缺少账单的个数
{
  if(mny==0)
  { //mny=0代表金额已经算清，可以把缺漏的金额输出来
    for(int i=0;i<num;i++)
    {
      cout<<lastm[i]<<" ";
    }
    cout<<endl;
    return;
  }
  for(int i=bm;i<=mny;i++)
  {
    if(total[i]>0)
    {  //如果这个金额是存在的，就将这个金额减去
      total[i]--;
      lastm[num]=i;
      dfs(mny-i,i,num+1);
      total[i]++;
    }
  }
}

int main()
{
  int money,n;
  cin>>money>>n;  //错的金额，记账清单个数
  int temp;
  for(int i=0;i<n;i++)
  {
    cin>>temp;  //输入每个账单的金额
    money-=temp;
    total[temp]++; //对应的金额是存在的，记为1
  }
  dfs(-money,0,0); //-money缺少的金额，0代表金额开始的数目（从小到大排列好的），0代表缺少的清单的个数
  return 0;
}

//https://www.lanqiao.cn/problems/291/learning/?page=8&first_category_id=1&sort=students_count&tags=%E7%9C%81%E8%B5%9B
