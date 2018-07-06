/*
Given a non-negative integer represented as non-empty a singly linked list of digits, plus one to the integer.

You may assume the integer do not contain any leading zero, except the number 0 itself.

The digits are stored such that the most significant digit is at the head of the list.

Example:
Input:
1->2->3

Output:
1->2->4

*/


class Solution {
public:
    ListNode* plusOne(ListNode* head) {
         if (!head) {
            return head;
        }
        int carry = help(head);
        if (carry == 1) {
            ListNode* res = new ListNode(1);
            res->next = head;
            return res;
        }
        return head;
    }
    int help(ListNode* head) {
        if (!head) {
            return 1;
        }
        int carry = help(head->next);
        int sum = head->val + carry;
        head->val = sum % 10;
        return carry = sum / 10;
        
    }
};
