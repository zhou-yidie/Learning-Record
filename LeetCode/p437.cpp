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
    unordered_map<long long, int> umap; // 记录每个前缀和出现的次数

    int dfs(TreeNode* root, int targetSum, long long cur){
        if(!root) return 0;

        int ret = 0;
        cur += root->val;
        ret += umap[cur - targetSum]; // cur-targetSum在之前出现的次数， map的默认值为0，即使这个key没添加过
        
        umap[cur]++;
        ret += dfs(root->left, targetSum, cur);
        ret += dfs(root->right, targetSum, cur);
        umap[cur]--;

        return ret;

    }

    int pathSum(TreeNode* root, int targetSum) {
        umap[0] = 1; // cur == targetSum时，是一条到根节点的路径
        return dfs(root, targetSum, 0);
    }


};


