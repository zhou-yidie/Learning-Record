int exgcd(int a,int b,int &x,int &y)
{
    if(b==0){x=1;y=0;return a;}
    int gcd=exgcd(b,a%b,x,y);
    int tp=x;
    x=y; y=tp-a/b*y;
    return gcd;
}

lt excrt()
{
    int x,y,k;
    int M=bi[1],ans=ai[1];//第一个方程的解特判
    for(int i=2;i<=n;i++)
    {
        int a=M,b=bi[i],c=(ai[i]-ans%b+b)%b;//ax≡c(mod b)
        int gcd=exgcd(a,b,x,y),bg=b/gcd;
        if(c%gcd!=0) return -1; //判断是否无解
        
        x=mul(x,c/gcd,bg);
        ans+=x*M;//更新前k个方程组的答案
        M*=bg;//M为前k个m的lcm
        ans=(ans%M+M)%M;
    }
    return (ans%M+M)%M;
}

//https://blog.csdn.net/niiick/article/details/80229217?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168311602216800222895014%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=168311602216800222895014&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~hot_rank-4-80229217-null-null.142^v86^wechat,239^v2^insert_chatgpt&utm_term=%E6%89%A9%E5%B1%95%E4%B8%AD%E5%9B%BD%E5%89%A9%E4%BD%99%E5%AE%9A%E7%90%86&spm=1018.2226.3001.4187
