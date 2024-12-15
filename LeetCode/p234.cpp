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
    bool isPalindrome(ListNode* head) {
        ListNode* cur = head;
        int cnt = 0 ;
        vector<int> v ;
        while( cur != nullptr ) {
            cnt++;
            v.push_back( cur->val ) ;
            cur = cur->next ;
        }
        int l = 0 , r = v.size() - 1 ;
        while( l < r ) {
            if( v[ l ] != v[ r ] ) {
                return false; 
            }
            l ++ ; r-- ;
        }
        return true;
    }
};
