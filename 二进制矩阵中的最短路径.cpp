class Solution 
{
private:
    int dirs[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) 
    {
        //由4个方向变为了8个方向
        int n = (int)grid.size();

        //grid[0][0] 和 grid[n - 1][n - 1]两个点为1 必不存在这样的路径
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;

        queue<pair<int, int>> q;//辅助队列
        q.emplace(pair(0, 0));//起始源点

        //这里为什么要初始化为1，因为题目中的路径是包含源点的，1 还可以记录为当前BFS的第一层
        //依次类推第二次应该为2... 这样不仅能区分该坐标有没有被访问，还能记录坐标的层数!
        grid[0][0] = 1;

        while (!q.empty()) 
        {
            //出队列
            auto [x, y] = q.front();
            q.pop();

            //8个方向的移动
            for (auto& dir : dirs) 
            {
                int nx = x + dir[0], ny = y + dir[1];//得到下一个坐标点

                //下一个坐标不越界且值为0
                if (nx >= 0 && nx < n && ny >= 0 && ny < n
                    && grid[nx][ny] == 0) 
                {

                    //同时该坐标0变为对应的层数
                    grid[nx][ny] = grid[x][y] + 1;
                    q.emplace(pair(nx, ny));//加入队列
                }
            }
        }

        //如果grid[n - 1][n - 1]还是0，说明不存在这样的路径，否则返回层数即为最短路径
        return grid[n - 1][n - 1] == 0 ? -1 : grid[n - 1][n - 1];
    }
};
