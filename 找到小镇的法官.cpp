class Solution 
{
public:
    int findJudge(int n, vector<vector<int>>& trust)   //看做有向图
    {
        vector<int> inDegrees(n + 1);
        vector<int> outDegrees(n + 1);
        for (auto& ans : trust) 
        {
            int x = ans[0], y = ans[1];
            ++inDegrees[y];
            ++outDegrees[x];
        }               // 入度为n-1,出度为0
        for (int i = 1; i <= n; ++i) 
        {
            if (inDegrees[i] == n - 1 && outDegrees[i] == 0) 
            {
                return i;
            }
        }
        return -1;
    }
};
