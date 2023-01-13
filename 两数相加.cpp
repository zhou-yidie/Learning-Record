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
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode *head = nullptr, *tail = nullptr;     //新定义一个头尾结点
        int carry = 0;
        while(l1 || l2)
        {
            int n1 = l1 ? l1->val:0;    //此时l1是否为空节点，若是，n1 = 0。
            int n2 = l2 ? l2->val:0;    //这里同理
            int sum = n1 + n2 + carry;  //同位相加
            if(!head)
            {
                head = tail = new ListNode(sum % 10);    //初始值便是个位相加
            }
            else
            {
                tail->next = new ListNode(sum%10);     //之后再尾插数据
                tail = tail->next;
            }
            carry = sum / 10;
            if(l1)
            {
                l1 = l1->next;     //往后遍历链表
            }
            if(l2)
            {
                l2 = l2->next;     //往后遍历链表
            }
        }
        if(carry > 0)
        {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};
