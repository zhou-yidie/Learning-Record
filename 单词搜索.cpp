class Solution {
public:
    //水平方向和垂直方向走法
    int xx[4] = { 1,-1, 0, 0};
    int yy[4] = { 0, 0, 1,-1};
    //算法函数（dfs+回溯）
    //board 和 word用引用可以大大缩短时间复杂度和空间复杂度，
    //除此以外，通过len递减也要快于新建一个变量到达len的长度(倒着寻找字符串)
    //x,y是搜索点的位置，a是行的边界值，b是列的边界值
    bool dfs(vector<vector<char>>& board, string& word,int x,int y,int len,int a,int b) {
        if(len==-1) return true;
        //标记搜索点为‘#’，搜索之后通过temp恢复原值
        char temp=word[len];
        //result用于判断是否已经找到
        bool result=false;
        int m,n; //新搜索点的位置
        for(int i=0;i<4;i++)
        {
            
            m=x+xx[i],n=y+yy[i];
            if(m>=0&&m<a&&n>=0&&n<b&&board[m][n]==word[len]) 
            {
                board[m][n]='#';
                //|= 按位或后赋值(a|=b等同于a=a||b)
                result|=dfs(board,word,m,n,len-1,a,b);
                board[m][n]=temp;
            }
        }
        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        //将word的长度先取出
        //取出字符串长度-1和矩阵边界值
        int len=word.length()-1;
        int a=board.size(),b=board[0].size();
        //标记搜索点为‘#’，搜索之后通过temp恢复原值
        char temp=word[len];
        for(int i=0;i<board.size();i++)
          for(int j=0;j<board[0].size();j++)
            {
                if(board[i][j]!=word[len]) continue;
                board[i][j]='#';
                //深度优先遍历（dfs）
                if(dfs(board,word,i,j,len-1,a,b)) return true;
                //回溯
                board[i][j]=temp;
            }
        return false;
    }
};

