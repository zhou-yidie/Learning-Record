class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int ans = -1 ;
        for (int i = 0 ; i < nums.size() ; i++ ) {
            int index = abs(nums[i]) ;
            if ( nums[index - 1] < 0) {
                return index;
                ans = index;
            }
            nums[index - 1] = -abs( nums[index - 1] ) ;
        }
        return ans;
    }
};
