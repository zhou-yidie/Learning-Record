class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int sz = nums.size();
        int dp[ sz + 5 ] ;
        for( int i = 0 ; i < sz + 3 ; i++ ) {
            dp[ i ]  = 1 ;
        }
        int ans = 1 ;
        for( int i = 0 ; i < sz ; i ++ ) {
            for( int j = 0 ; j < i ; j ++ ) {
                if( nums[j] < nums[ i ] ) {
                    dp[ i ] = max( dp[ i ] , dp[ j ] + 1 ) ;
                    ans = max( ans , dp[ i ] ) ;
                }
            }
        }
        // for( int i = 0 ; i < sz ; i++ ) {
        //     cout << dp[ i ] << " " ;
        // }
        return ans ;
    }
};
