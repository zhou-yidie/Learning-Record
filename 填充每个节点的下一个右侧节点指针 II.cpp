/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        Node* p;
        //若树为空，则直接返回树的根结点
        if(root==NULL) return root;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            //这里的len即某一层的结点总数
            int len=q.size();
            Node* pre=NULL;
            //遍历该层结点
            for(int i=0;i<len;i++){
                //取队头结点并弹出它
                p=q.front();
                q.pop();
                if(pre) pre->next=p;
                pre=p; 
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
        }
        return root;
    }
};

