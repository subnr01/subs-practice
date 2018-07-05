/*
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5

*/


class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(!head) return NULL;
        ListNode * newHead = new ListNode(0);
        newHead->next = head;
        ListNode* cur = newHead;
        while(cur ){
            while( cur->next && cur->next->val == val ){
                cur->next = cur->next->next;
            }
            cur = cur->next;
        }
        
        return newHead->next;
    }
};
