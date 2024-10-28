/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution 
{
public:
    ListNode* swapPairs(ListNode* head) 
    {
        ListNode* dummyHead = new ListNode(0);   //创建一个哑结点
        dummyHead->next = head;                  //next指针指向head
        ListNode* temp = dummyHead;
        while (temp->next != nullptr && temp->next->next != nullptr)    //交换前提，这个结点的后面和后面的后面不为空
        {
            ListNode* node1 = temp->next;         //交换过程
            ListNode* node2 = temp->next->next;
            temp->next = node2;
            node1->next = node2->next;
            node2->next = node1;
            temp = node1;
        }
        return dummyHead->next;
    }
};

