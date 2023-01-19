class Solution 
{
public:
    bool canJump(vector<int>& nums) 
    {
        int n = nums.size();
        int Rmost = 0;
        for(int i = 0; i < n; i++)
        {
            if(i <= Rmost)
            {
                Rmost = max(Rmost, i + nums[i]);
            }
            if(Rmost >= n-1)
            {
                return true;
            }
        }

        return false;
    }
};


