class Solution 
{
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& f, vector<vector<int>>& s) 
    {
        int n=s.size(),m=f.size();
        vector<vector<int>> res;

        if(n==0 || m==0) return res;
        for(int i=0;i<n;i++){
            int t1=s[i][0];
            
            //找到 >= t1的最小的右边界
            int left=-1,right=m;
            while(right!=left+1)
            {
                int mid=(left+right)/2;
                if(f[mid][1] < t1) left=mid;
                else right=mid;
            }
            if(right == m)  return res; //后面不会再有交集了
            int f1=right;

            //找到 <=t2 的最大的左边界
            int t2=s[i][1];
            left=-1,right=m;
            while(right!=left+1)
            {
                int mid=(left+right)/2;
                if(f[mid][0]<=t2) left=mid;
                else right=mid;
            }
            int f2=left;
            
            for(int j=f1;j<=f2;j++)
            {
                res.push_back(vector<int>{ max(t1, f[j][0]) ,min(t2, f[j][1])} );
            }
        }
        return res;
    }
};

