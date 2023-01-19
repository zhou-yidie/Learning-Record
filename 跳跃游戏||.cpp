class Solution 
{
public:
    int jump(vector<int>& nums) 
    {
        int Rmost = 0, n = nums.size(), end = 0, step = 0;
        for (int i = 0; i < n - 1; ++i) 
        {
            if (Rmost >= i) 
            {
                Rmost = max(Rmost, i + nums[i]);
            }
            if (i == end) 
            {
                end = Rmost;
                ++step;
            }
        }
        return step;
    }
};

