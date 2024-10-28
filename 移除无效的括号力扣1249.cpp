class Solution 
{
public:
    string minRemoveToMakeValid(string s) 
    {
        stack<int> braket;
        int sLen = s.size();
        for(int i =0; i<sLen ; ++i)
        {
            if(s[i] == '(' || s[i] == ')')
            {
                if(s[i] == '(') braket.push(i);
                else if(braket.empty()) 
                {
                    s.erase(i,1);
                    --sLen;
                    --i;
                }
                else braket.pop();
            }
        }
        
        while(!braket.empty())
        {
            int i = braket.top();
            s.erase(i,1);
            braket.pop();
        }
        return s;
    }
};

//https://leetcode.cn/problems/minimum-remove-to-make-valid-parentheses/submissions/
