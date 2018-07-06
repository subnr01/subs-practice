/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/



// O(N) time, O(1) space in total
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == NULL) return;
        ListNode *fast = head, *slow = head;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        ListNode *second = reverseList(slow->next);
        slow->next = NULL;
        ListNode *first = head;
        
        while (first && second) {
            ListNode *t1 = first->next, *t2 = second->next;
            first->next = second;
            second->next = t1;
            first = t1;
            second = t2;
        }
    }
private:
    ListNode *reverseList(ListNode *head) {
        ListNode *prev = NULL;
        while (head) {
            ListNode *next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};
