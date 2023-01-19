class Solution 
{
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
        int i = 0, n = gas.size();
        while(i < n)
        {
            int Gas = 0, Cost = 0;
            int sum = 0;                           //经过加油站的总数
            while(sum < n)
            {
                int j = (i + sum) % n;
                Gas +=gas[j];
                Cost += cost[j];
                if(Cost > Gas)
                {
                    break;
                }
                sum++;
            }
            if(sum == n)
            {
                return i;
            }
            else
            {
                i = i + sum +1;
            }
        }
        return -1;   
    }
};

