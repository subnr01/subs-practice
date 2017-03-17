/*

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* cur = head;
        while(cur) {
        	while(cur->next && cur->val == cur->next->val) {
        		cur->next = cur->next->next;
        	}
        	cur = cur->next;
        }
        return head;
    }
};
