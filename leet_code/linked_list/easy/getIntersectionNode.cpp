/*
Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.

*/

//shorter soln
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* a = headA;
        ListNode* b = headB;
        while (a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }
        return a;
    }
};

//longer soln
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;
        int nA=0,nB=0;
        ListNode *p=headA;
        while(p) {
            nA++;
            p=p->next;
        }
        p=headB;
        while(p) {
            nB++;
            p=p->next;
        }
        ListNode* q;
        int diff;
        if(nA>=nB) {
            p=headA;
            q=headB;
            diff=nA-nB;
        }
        else {
            p=headB;
            q=headA;
            diff=nB-nA;
        }
        while(diff--) {
            p=p->next;
        }
        while(p && q) {
            if(p==q) return p;
            p=p->next;
            q=q->next;
        }
        return NULL;
        
    }
};
