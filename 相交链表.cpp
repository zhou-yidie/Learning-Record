/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution 
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        if(headA == nullptr || headB == nullptr)
        {
            return nullptr;
        }

        ListNode *A = headA, *B = headB;
        while(A != B)                       //遍历最短链表两次便可得到结果。
        {
            A = A == nullptr? headB : A->next;     
            B = B == nullptr? headA : B->next;
        }           //循环结束后若没有相交结点  则返回空节点
        return A;
    }
};
