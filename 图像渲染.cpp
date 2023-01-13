// 广度优先
class Solution 
{
public:
    const int dx[4] = {1, 0, 0, -1};
    const int dy[4] = {0, 1, -1, 0};
    
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) 
    {
        int currColor = image[sr][sc];
        if (currColor == color) 
        {
            return image;
        }
        
        int n = image.size(), m = image[0].size();
        queue<pair<int, int>> que;
        que.emplace(sr, sc);
        image[sr][sc] = color;
        while (!que.empty()) 
        {
            int x = que.front().first, y = que.front().second;
            que.pop();
            for (int i = 0; i < 4; i++) 
            {
                int mx = x + dx[i], my = y + dy[i];
                if (mx >= 0 && mx < n && my >= 0 && my < m && image[mx][my] == currColor) 
                {
                    que.emplace(mx, my);
                    image[mx][my] = color;
                }
            }
        }
        return image;
    }
};

//深度优先
class Solution 
{
public:
    const int dx[4] = {1, 0, 0, -1};
    const int dy[4] = {0, 1, -1, 0};
  
    void dfs(vector<vector<int>>& image, int x, int y, int currColor, int color) 
    {
        if (image[x][y] == currColor) 
        {
            image[x][y] = color;
            for (int i = 0; i < 4; i++) 
            {
                int mx = x + dx[i], my = y + dy[i];
                if (mx >= 0 && mx < image.size() && my >= 0 && my < image[0].size()) 
                {
                    dfs(image, mx, my, currColor, color);
                }
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) 
    {
        int currColor = image[sr][sc];
        if (currColor != color) 
        {
            dfs(image, sr, sc, currColor, color);
        }
        return image;
    }
};

