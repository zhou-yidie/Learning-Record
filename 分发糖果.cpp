class Solution 
{
public:
    int candy(vector<int>& ratings) 
    {
        int n = ratings.size();
        int ret = 1;
        int inc = 1, dec = 0, pre = 1;            //inc代表递增,dec代表递减。
        for (int i = 1; i < n; i++) 
        {
            if (ratings[i] >= ratings[i - 1]) 
            {
                dec = 0;
                pre = ratings[i] == ratings[i - 1] ? 1 : pre + 1;
                ret += pre;
                inc = pre;
            } 
            else 
            {
                dec++;
                if (dec == inc) 
                {
                    dec++;
                }
                ret += dec;
                pre = 1;
            }
        }
        return ret;
    }
};

