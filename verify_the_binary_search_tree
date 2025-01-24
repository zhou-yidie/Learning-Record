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
 
 //力扣上P89验证二叉搜索树--中序遍历解法
 
class Solution 
{
    long pre = LONG_MIN;
public:
    bool isValidBST(TreeNode* root) 
    {
        if(root == nullptr)    //如果为空，直接判断正确，因为空节点是合理的二叉搜索树
        {
            return true;
        }
        if(!isValidBST(root->left) || pre >= root->val)   //访问左子树
        {
            return false;
        }
        // if(pre >= root->val)      //判断当前节点和前一个节点的大小关系
        // {
        //     return false;
        // }
        pre = root->val;
        return isValidBST(root->right);  //再访问右节点
    }
};
