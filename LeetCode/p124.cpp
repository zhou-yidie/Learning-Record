/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = -1001;
    pair<int,int> dfs(TreeNode* cur) {
        if (cur == nullptr) {
            return {0 , 0};
        }
        int cur_val = cur->val;
        
        auto m_left = dfs(cur->left);
        auto m_right = dfs(cur->right);
        
        int one_val = max( max(m_left.first, m_right.first), 0 ) + cur_val;
        int two_val = max(0,m_left.first + m_right.first) + cur_val;
        ans = max(ans,one_val);
        ans = max(ans,two_val);
        pair<int,int> res = {one_val,two_val};
        return res;
        
    }
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return ans;
    }
};
