class Solution 
{
public:
    vector<int> path;
    vector<vector<int>> result;
    void backTracking(vector<int>& candidates, int sum, int target, int startIndex) 
    {
        if (sum > target) 
        {
            return;
        }
        if (sum == target) 
        {
            result.emplace_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size(); ++i) 
        {
            sum += candidates[i];
            path.emplace_back(candidates[i]);
            backTracking(candidates, sum, target, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) 
    {
        if (candidates.size() == 0) return {};
        backTracking(candidates, 0, target, 0);
        return result;
    }
};

