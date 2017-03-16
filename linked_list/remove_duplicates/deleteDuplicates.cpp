/*

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/



class Solution {
public:
    ListNode* deleteDuplicates(ListNode* h) {
        if (h && (h->next = deleteDuplicates(h->next)) && h->next->val == h->val) {
            delete h;
            h = h->next; 
        }
        
       
        return h;

        
    }
};
