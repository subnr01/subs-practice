/*

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, 
only nodes itself can be changed.
*/

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        //ptr ponits to the address of listnode
        ListNode **ptr = &head;
        ListNode *first;
        first = head;
        
        while (first && first->next)
        {
            ListNode *second = first->next;
            first->next=second->next;
            second->next=first;
            //*ptr points to listnode
            *ptr=second;
            ptr=&(first->next);
            first = *ptr;
        } 
        return head;
    }
};
