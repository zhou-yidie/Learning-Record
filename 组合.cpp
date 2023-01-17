//字典序法

class Solution 
{
public:
    void backtrack(vector<vector<int>>& res, vector<int>& output, int first, int len)
    {
        // 所有数都填完了
        if (first == len) 
        {
            res.emplace_back(output);
            return;
        }
        for (int i = first; i < len; ++i) 
        {
            // 动态维护数组
            swap(output[i], output[first]);
            // 继续递归填下一个数
            backtrack(res, output, first + 1, len);
            // 撤销操作
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) 
    {
        vector<vector<int> > res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};



//递归
class Solution 
{
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int n, int k) 
    {
        // 剪枝：temp 长度加上区间 [cur, n] 的长度小于 k，不可能构造出长度为 k 的 temp
        if (temp.size() + (n - cur + 1) < k) 
        {
            return;
        }
        // 记录合法的答案
        if (temp.size() == k) 
        {
            ans.push_back(temp);
            return;
        }
        // 考虑选择当前位置
        temp.push_back(cur);
        dfs(cur + 1, n, k);
        temp.pop_back();
        // 考虑不选择当前位置
        dfs(cur + 1, n, k);
    }

    vector<vector<int>> combine(int n, int k) 
    {
        dfs(1, n, k);
        return ans;
    }
};


