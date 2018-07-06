/*

Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
*/


class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *p = head;
        ListNode *pre = head;
        while (n > 0) {
            if (!p) break;
            p = p->next;
            n--;
        }
        if (p == NULL) {
            return head->next;
        }

        while (p->next != NULL) {
            p = p->next;
            pre = pre->next;
        }
        ListNode *next = pre->next;
        pre->next = pre->next->next;
        delete next;
        return head;
    }
};
