class Solution {
public:
   int orangesRotting(vector<vector<int>>& grid) {
        int row=grid.size();
        int col=grid[0].size();
        int res=0;
        vector<int>dx={-1,0,0,1};//辅助定位即将被腐烂的橘子的横坐标
        vector<int>dy={0,1,-1,0};//辅助定位即将被腐烂的橘子的纵坐标，对应构成腐烂橘子的四个污染方向
        queue<pair<int,int>>rot ;
        for(int i=0;i<row;++i)//将腐烂橘子一一压入队列
            for(int j=0;j<col;++j)
                if(grid[i][j]==2)
                    rot.push({i,j});
        while(!rot.empty())
        {
            int vol=rot.size();//标记队列内腐烂橘子个数
            for(int i=0;i<vol;++i)
            {
                pair<int,int> fir=rot.front();//取出首个腐烂橘子
                rot.pop();
                for(int j=0;j<4;++j)//进行四个方向污染
                {
                    int x=fir.first+dx[j],y=fir.second+dy[j];
                    if(x>=0&&x<row&&y>=0&&y<col&&grid[x][y]==1)//判断是否存在新鲜橘子
                    {
                        grid[x][y]=2;
                        rot.push({x,y});
                    }
                }
            }
            if(!rot.empty())//如果为空表示一开始就没有腐烂橘子，返回0分钟
                res++;//每次取出队列所有橘子时间加1，同时压入被污染的新一批橘子
        }
        for(int i=0;i<row;++i)//检查是否还有新鲜橘子
            for(int j=0;j<col;++j)
                if(grid[i][j]==1)
                    return -1;
        return res;
    }
};
