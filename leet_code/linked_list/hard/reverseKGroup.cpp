/*

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

*/

//Recusursive soln
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k <= 1) {
            return head;
        }
        
        ListNode dummy(-1);
        ListNode *pre = &dummy;
        pre->next = head;
        ListNode *curr = head;
        ListNode *nxt = NULL;
        
        int n = 0;
        
	// find the total number of nodes
        while (curr) {
            n++;
            curr = curr->next;
        }
        
        while (n >= k)
        {
            curr = pre->next;
            nxt = curr->next;
		
	    // go (k - 1) nodes
            for (int i = 1; i < k; i++)
            {
                curr->next = nxt->next;
                nxt->next = pre->next;
                pre->next = nxt;
                nxt = curr->next;
            }
            n -= k;
            pre = curr;
        }
        
        return dummy.next;
    }
};


//iterative (which I do not like so much)
class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) 
    {
        if(!head || k <= 1) 
        {
            return head;
        }
        
        int num = 0;
        ListNode dummy(-1);
        ListNode *cur = &dummy;
        ListNode *pre = cur;
        ListNode *nex = NULL;
        
        cur->next = head;
        
	//Find the total number of nodes
        while(cur = cur->next) {
            num++;
        }
        
	//Reverse for every k nodes
	//until num > k
        while(num >= k) 
        {
            cur = pre->next;
            nex = cur->next;
            for(int i = 1; i < k; ++i) 
            {
                cur->next = nex->next;
                nex->next = pre->next;
                pre->next = nex;
                nex = cur->next;
            }
            pre = cur;
            num -= k;
        }
        return dummy.next;
    }
};
