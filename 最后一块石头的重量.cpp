class Solution 
{
public:
    int lastStoneWeight(vector<int>& stones) 
    {
        while(stones.size() > 1)
        {
            int n = stones.size();
            sort(stones.begin(),stones.end());
            int x = stones[n-2];
            int y = stones[n-1];
            stones.pop_back();
            stones.pop_back();
            if(stones[n-1] != stones[n-2])
            {
                stones.push_back(y-x);
            }
        }
        if(stones.size() == 0)
        {
            return 0;
        }
        else
        {
            return stones[0];
        }
    }
};


class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> q;
        for (int s: stones) {
            q.push(s);
        }

        while (q.size() > 1) {
            int a = q.top();
            q.pop();
            int b = q.top();
            q.pop();
            if (a > b) {
                q.push(a - b);
            }
        }
        return q.empty() ? 0 : q.top();
    }
};

