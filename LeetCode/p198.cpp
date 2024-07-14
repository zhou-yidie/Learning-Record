class Solution {
public:
    int rob(vector<int>& nums) {
        //int size = nums.size() ;
        int qu = 0 , bu = 0 ;
        for( int i = 0 ; i < nums.size() ; i++ ) {
            int tmp = qu ;
            qu = bu + nums[ i ] ;

            bu = max( tmp , bu ) ;
        

            // int j = i + 1 ; 
            // dp[j][1] = dp[ j - 1 ][ 0 ] + nums[ i ] ;
            // dp[ j ][ 0 ] = max( dp[ j-1 ][0] , dp[ j -1 ][ 1 ] ) ;
        }
        return max( qu,bu ) ;
    }
};
