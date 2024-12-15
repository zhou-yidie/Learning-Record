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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *p = head;
        for(int i = 0; i < k; i++) {
            if(!p) return head;
            p = p->next;
        }

        ListNode *q = head;
        ListNode *pre = nullptr;
        while(q != p) {
            ListNode *tmp = q->next;
            q->next = pre;
            pre = q;
            q = tmp;
        }

        head->next = reverseKGroup(p, k);
        return pre;
    }
};

