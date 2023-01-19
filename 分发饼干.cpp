class Solution 
{
public:
    int findContentChildren(vector<int>& g, vector<int>& s) 
    {
        int n1 = g.size(), n2 = s.size();
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int i = 0, j = 0, sum = 0;
        while(i < n1 && j < n2)
        {
            if(s[j] >= g[i])
            {
                sum++;
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }
        return sum;
    }
};
