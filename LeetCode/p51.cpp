class Solution
{
    vector<vector<string>> ret;
    vector<string> board;
    bool col[10];
    bool diag1[20];//主对角线 --- y - x + n = b + n
    bool diag2[20];//副对角线 --- y + x = b
    int n;
public:
    void dfs(int i)
    {
        if(i == n)
        {
            ret.push_back(board);
            return;
        }
        
        for(int j=0; j<n; ++j)
        {
            if(!col[j] && !diag1[i - j + n] && !diag2[i + j])
            {
                col[j] = diag1[i - j + n] = diag2[i + j] = true;
                board[i][j] = 'Q';
                dfs(i + 1);
                board[i][j] = '.';
                col[j] = diag1[i - j + n] = diag2[i + j] = false;
            }
        }
    }

    vector<vector<string>> solveNQueens(int _n)
    {
        n = _n;
        board.resize(n, string(n, '.'));
        dfs(0);
        return ret;
    }
};
