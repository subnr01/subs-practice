/*
Given a singly linked list, determine if it is a palindrome.

Could you do it in O(n) time and O(1) space?
*/


/*
Solution

*/

//cleaner soln
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL||head->next==NULL)
            return true;
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast->next!=NULL&&fast->next->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }
        slow->next=reverseList(slow->next);
        slow=slow->next;
        while(slow!=NULL){
            if(head->val!=slow->val)
                return false;
            head=head->next;
            slow=slow->next;
        }
        return true;
    }
    ListNode* reverseList(ListNode* head) {
        ListNode* pre=NULL;
        ListNode* next=NULL;
        while(head!=NULL){
            next=head->next;
            head->next=pre;
            pre=head;
            head=next;
        }
        return pre;
    }
};


class Solution {
private:
	bool isSameList(ListNode *node0, ListNode *node1) {
		while(node0 && node1) {
			if (node0->val != node1->val) return false;
			node0 = node0->next;
			node1 = node1->next;
		}
		//if (node0 || node1) return false;
		return true;
	}
public:
    bool isPalindrome(ListNode* head) {
        ListNode *pre = NULL, *fast = head, *slow = head;
        while(fast && fast->next) {		//reverse list
        	fast = fast->next->next;
        	ListNode *tmp = slow;
        	slow = slow->next;
        	tmp->next = pre;
        	pre = tmp;
        }
        if(fast != NULL) {
		//Skip over the centre element
        	slow = slow->next;
        }
        return isSameList(pre, slow);
    }
};
