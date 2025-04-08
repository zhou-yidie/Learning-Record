class Solution {
    public:
        const int mod = 1e9+7;
        int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
            long long ans = 0;
            int n = nums.size();
            long long mx = 0;
            for (int v : nums) {
                mx = max(mx,(long long)v);
            }
            long long sum = 0;
            long long mx2 = 0;
            for (int v: nums) {
                long long cha = mx - v;
                sum += cha;
                mx2 = max(mx2,cha);
            }
    
            if (nums.size() <= 2 || cost2 >= 2 * cost1) {
                ans = (sum * cost1) % mod;
                return ans;
            }
    
    
    
            ans = LONG_LONG_MAX;
            for (int i = mx; i <= 2*mx; ++i) {
                long long tmp = 0;
                if (mx2 <= sum - mx2) {
                    tmp = (sum / 2 * cost2) ;
                    if (sum & 1) {
                        tmp += cost1;
                    }
                } else {
                    tmp = ((sum - mx2) * cost2) ;
                    long long tp2 = 2 * mx2 - sum;
                    tmp += (tp2 * cost1); 
                }
                ans = min(ans,tmp);
                sum += n;
                mx2++;
            }
            return ans % mod;
        }
    };
    