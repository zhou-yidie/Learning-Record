class Solution 
{
public:
    vector<string> letterCasePermutation(string s) 
    {
        int n = s.size();
        int m = 0;
        for (auto c : s) 
        {
            if (isalpha(c)) 
            {
                m++;
            }
        }

        vector<string> ans;
        for (int mask = 0; mask < (1 << m); mask++) 
        {
            string str;
            for (int j = 0, k = 0; j < n; j++) 
            {
                if (isalpha(s[j]) && (mask & (1 << k++))) 
                {
                    str.push_back(toupper(s[j]));
                } 
                else 
                {
                    str.push_back(tolower(s[j]));
                }
            }
            ans.emplace_back(str);
        }
        return ans;
    }
};

