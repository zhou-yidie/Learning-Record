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
    vector<int> res;
    void dfs(TreeNode* cur) {
        if (cur->left != nullptr) {
            dfs(cur->left);
        }
        res.push_back(cur->val);
        if (cur->right) {
            dfs(cur->right);
        }
        return;
    }
    vector<int> inorderTraversal(TreeNode* root) {
        res.clear();
        if (root != nullptr) {
            dfs(root);
        }
        return res;
    }
};
