class Solution 
{
public:
    int minimumOperations(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        int ans, n = unique(nums.begin(), nums.end()) - nums.begin();
        ans = n;
        for (int i = 0; i < n; i++) 
        {
            if (!nums[i]) 
            {
                ans--;
            } 
            else 
            {
                break;
            }
        }
        return ans;
    }
};

