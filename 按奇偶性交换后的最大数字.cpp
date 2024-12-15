class Solution 
{
public:
    int largestInteger(int num) 
    {
        string s = to_string(num);   // 转化为字符串
        int n = s.size();
        // 进行选择排序
        for (int i = 0; i < n - 1; ++i) 
        {
            for (int j = i + 1; j < n; ++j) 
            {
                // 只有下标数值奇偶相同才进行判断
                if ((s[i] - s[j]) % 2 == 0 && s[i] < s[j]) 
                {
                    swap(s[i], s[j]);
                }
            }
        }
        // 转化为最终的整数
        return stoi(s);
    }
};

