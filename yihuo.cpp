class Solution
{
	public:
		int singleNumber(vector<int>& nums)
		{
			int val = nums[0];    //把初值赋给val;
			for(int i = 1; i < nums.size(); i++)   //再一个一个遍历异或
			{
				val ^= nums[i];
			}
			return val;
		}
};   //LeetCodeP136
//时间复杂度O(N),空间复杂度O(1)。
