#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,r,c,i;
    cin>>n>>m;
    int t=0,b=n-1,l=0,ri=m-1;
    cin>>r>>c;
    long long a[1005][1005],cnt=1;
    while(cnt<=m*n)
    {
        for(i=l;i<=ri;i++)
        {
            a[t][i]=cnt;
            cnt++;
        }
        t++;
        for(i=t;i<=b;i++)
        {
            a[i][ri]=cnt;
            cnt++;
        }
        ri--;
        for(i=ri;i>=l;i--)
        {
            a[b][i]=cnt;
            cnt++;
        }
        b--;
        for(i=b;i>=t;i--)
        {
            a[i][l]=cnt;
            cnt++;
        }
        l++;
    }
    cout<<a[r-1][c-1]<<endl;
    return 0;
}
