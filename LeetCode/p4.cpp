class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size() , s= n + m;
        double s_2 , s_21;
        int cnt = 0 , i = 0 , j = 0;
        while( i < n && j < m && cnt <= s/2 ) {
            if( nums1[i] <= nums2[j]  ) {
                if (cnt == s/2-1) {
                    s_21 =nums1[i];
                } else if (cnt == s/2) {
                    s_2 = nums1[i];
                }
                i++;
            } else {
                if (cnt == s/2-1) {
                    s_21 =nums2[j];
                } else if (cnt == s/2) {
                    s_2 = nums2[j];
                }
                j++;
            }
            cnt++;
        }
        while( i == n && j < m && cnt <= s/2 ) {
            if (cnt == s/2-1) {
                s_21 =nums2[j];
            } else if (cnt == s/2) {
                s_2 = nums2[j];
            }
            j++;
            cnt++;
        }
        while( i < n && j == m && cnt <= s/2 ) {

            if (cnt == s/2-1) {
                s_21 =nums1[i];
            } else if (cnt == s/2) {
                s_2 = nums1[i];
            }
           i++;
           cnt++;
        }
        if( s & 1 ) {
            return s_2;
        } else {
            return  (s_2 + s_21)/2 ;
        }
    }
};
