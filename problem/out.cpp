#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <time.h>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;
char strin[5]=".in";
char strout[5]=".out";
char head[4];

int a[100010] , s[100010] , ans[100010];

int main()
{
	FILE* fp;
	FILE* fo;
	int b,c;
	for(int i=1;i<=1;i++)
	{
		sprintf(head,"%d",i);
		fp = fopen(strcat(head,strin),"r");//找到对应的.in 


		sprintf(head,"%d",i);
		fo = fopen(strcat(head,strout),"w");//找到对应的.out 

        int n ;
        int mi = 10010,semi = 10010;
        a[0] = s[0] = 0 ;
		fscanf(fp,"%d",&n);//读取对应的.in中的数据 (注意读数据的写法)
        for (int j = 1 ; j <= n ; j++ ) {
            fscanf(fp,"%d",&a[j]);
    
            s[j] = s[j-1] + a[j];
            if (a[j] <= mi) {
                semi = mi ; mi = a[j] ;
            } else if (a[j] <= semi) {
                semi = a[j];
            }
            if (j == 1) {
                ans[j] = 0 ;
            } else if (j == 2) {
                ans[j] = max(a[2] , a[1]) ;
            } else {
                ans[j] = 2 * s[j] - mi - semi ;
            }
        }
        for (int j = 1 ; j <= n ; j++ ) {
            fprintf(fo,"%d ",ans[j]);//写入对应的.out 
        }
	}
	return 0;
}