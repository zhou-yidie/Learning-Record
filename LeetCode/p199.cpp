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
    vector<int> ans;
    vector<int> rightSideView(TreeNode* root) {
        queue<pair<TreeNode*,int> > qu;
        if (root != nullptr) {
            qu.push( {root,1} ) ;
        }
        while (!qu.empty()) {
            TreeNode* now = qu.front().first;
            int depth = qu.front().second;
            if (depth > ans.size()) {
                ans.push_back(now->val);
            } else {
                ans[ depth - 1 ] = now->val;
            }
            qu.pop();
            if (now->left != nullptr) {
                qu.push({now->left , depth + 1}) ;
            }
            if (now->right != nullptr) {
                qu.push({now->right , depth + 1}) ;
            }
        }
        return ans;
    }
};
