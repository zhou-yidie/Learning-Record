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

class Solution 
{
public:
    int kthSmallest(TreeNode* root, int k) 
    {
        stack<TreeNode*> stack;                    //定义一个stack栈容器，存储节点
        while (root != nullptr || stack.size() > 0)      //只要两者有一者为空，则继续循环。
        {
            while (root != nullptr) 
            {
                stack.push(root);         //节点入栈
                root = root->left;        //节点往左遍历
            }
            root = stack.top();
            stack.pop();                  //最外的顶点出栈
            --k;                          //k的次数减少。
            if (k == 0) 
            {
                break;
            }
            root = root->right;
        }
        return root->val;
    }
};

