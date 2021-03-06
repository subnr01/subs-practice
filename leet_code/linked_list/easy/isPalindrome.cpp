/*
Given a singly linked list, determine if it is a palindrome.

Could you do it in O(n) time and O(1) space?
*/


/*
Solution

*/

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;
        }
        stack<int> st;
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        
        
        while (fast && fast->next)
        {
            st.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if (fast) {
            slow = slow->next;
        }
        
        while (slow)
        {
            int temp = slow->val;
            if (temp != st.top()) {
                return false;
            }
            st.pop();
            slow = slow->next;
        }
        return true;
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
