class Solution 
{
public:
    int findCircleNum(vector<vector<int>>& isConnected) 
    {
        int cities = isConnected.size();
        vector<int> visited(cities);
        int provinces = 0;
        queue<int> Q;
        for (int i = 0; i < cities; i++) 
        {
            if (!visited[i]) 
            {
                Q.push(i);
                while (!Q.empty()) 
                {
                    int j = Q.front(); Q.pop();
                    visited[j] = 1;
                    for (int k = 0; k < cities; k++) 
                    {
                        if (isConnected[j][k] == 1 && !visited[k]) 
                        {
                            Q.push(k);
                        }
                    }
                }
                provinces++;
            }
        }
        return provinces;
    }
};
