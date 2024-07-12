class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st;
        for (int num : nums) {
            st.insert(num);
        }   
        int ans = 0 ;
        for ( int val : st) {
            if (!st.count(val - 1)) {
                int cur = val ;
                int tmp = 1 ; 

                while (st.count(cur + 1)) {
                    cur ++ ;
                    tmp ++;
                }
                ans=  max( ans , tmp);
            }
        }
        return ans ;
    }
};
