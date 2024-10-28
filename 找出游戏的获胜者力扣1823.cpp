//队列＋模拟

class Solution 
{
public:
    int findTheWinner(int n, int k) 
    {
        queue<int> qu;
        for (int i = 1; i <= n; i++) 
        {
            qu.emplace(i);
        }
        while (qu.size() > 1) 
        {
            for (int i = 1; i < k; i++) 
            {
                qu.emplace(qu.front());
                qu.pop();
            }
            qu.pop();
        }
        return qu.front();
    }
};

//递归+迭代
class Solution {
public:
    int findTheWinner(int n, int k) {
        if (n == 1) {
            return 1;
        }
        return (k + findTheWinner(n - 1, k) - 1) % n + 1;
    }
};

class Solution {
public:
    int findTheWinner(int n, int k) {
        int winner = 1;
        for (int i = 2; i <= n; i++) {
            winner = (k + winner - 1) % i + 1;
        }
        return winner;
    }
};

//https://leetcode.cn/problems/find-the-winner-of-the-circular-game/solution/
