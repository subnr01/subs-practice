/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/



class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return head;
        
        int len=1; // number of nodes
        ListNode *newH, *tail;
        newH=tail=head;
        
        while(tail->next)  // get the number of nodes in the list
        {
            tail = tail->next;
            len++;
        }
        k %= len;
        if (!k) {
            return head;
        }
        tail->next = head; // circle the link
        
        for(auto i=0; i<len-k; i++) 
            tail = tail->next; 
        
        newH = tail->next; 
        tail->next = NULL;
        return newH;
    }
};
