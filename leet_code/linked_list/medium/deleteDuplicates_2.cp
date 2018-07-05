/*
Given a sorted linked list, delete all nodes that have duplicate numbers,
leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.

*/




class Solution {
public:
   ListNode* deleteDuplicates(ListNode* head){
    	if(head == NULL || head->next == NULL) return head;
    	ListNode dummy(0);
    	dummy.next = head;
    	head = &dummy;

    	while(head->next && head->next->next){
    		if(head->next->val == head->next->next->val){
    			int val = head->next->val;
    			while(head->next && head->next->val == val){
                    ListNode *temp = head->next;
    				head->next = head->next->next;
                    free(temp);
    			}
    		}else{
    			head = head->next;
    		}
    	}
    	return dummy.next;
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
