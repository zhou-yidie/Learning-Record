class Solution 
{
public:
    int fillCups(vector<int>& amount) 
    {
        int sum = 0;
        sort(amount.begin(),amount.end());
        if((amount[0] + amount[1]) <= amount[2])
        {
            return amount[2];
        } 
        else
        {
            sum += amount[2];
            for(int i = 0; i < amount[2]; i++)
            {
                if(amount[1] >= amount[0])
                {
                    amount[1] -= 1;
                }
                else
                {
                    amount[0] -=1;
                }
            }
            sum += max(amount[0],amount[1]);
            return sum;
        }   
    }
};
