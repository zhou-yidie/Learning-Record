class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                ans += min( leftMax - height[left] , rightMax - height[left] ) ;
                ++left;
            } else {
                ans += min( leftMax - height[right] , rightMax - height[right] ) ;
                --right;
            }
        }
        return ans;
    }
};
