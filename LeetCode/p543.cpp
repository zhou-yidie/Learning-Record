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
    int ans ;
    int dfs(TreeNode* cur){
        if (cur == nullptr) {
            return 0;
        }
        int L = dfs(cur->left);
        int R = dfs(cur->right);
        ans = max(ans , L + R + 1) ;
        return max(L,R) + 1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        dfs(root);
        return ans-1;
    }
};
