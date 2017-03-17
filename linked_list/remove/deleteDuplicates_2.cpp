/*
Given a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

*/





class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode **runner = &head;
        
        if(!head || !head->next)return head;
        
        while(*runner)
        {
            if((*runner)->next && (*runner)->next->val == (*runner)->val)
            {
                ListNode *temp = *runner;
                while(temp && (*runner)->val == temp->val)
                    temp = temp->next;
                
                *runner = temp;
            }
            else
                runner = &((*runner)->next);
        }
        
        return head;
    }
};

/*
recursive

*/


class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return 0;
        if (!head->next) return head;
        
        int val = head->val;
        ListNode* p = head->next;
        
        if (p->val != val) {
            head->next = deleteDuplicates(p);
            return head;
        } else {
            while (p && p->val == val) p = p->next;
            return deleteDuplicates(p);
        }
    }
};
