
//Find middle node of the singly linked list

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *fast = head;
        ListNode *slow = head;
        
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
        
    }
};
