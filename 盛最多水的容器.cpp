class Solution 
{
public:
    int maxArea(vector<int>& height) 
    {
        int n = height.size();
        int left = 0, right = n-1;
        int S = 0;
        while(left < right)
        {
            int h = height[left] > height[right] ? height[right] : height[left];
            int preS = (right - left) * h;
            S = preS > S ? preS : S;
            if(height[left] <= height[right])
            {
                left++;
            }
            else
            {
                right--;
            }
        }
        return S;
    }
};
