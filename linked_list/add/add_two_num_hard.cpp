/*

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order 
and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    vector<int> convertToVector(ListNode *head) {
        vector<int> res;
        while (head) {
            res.push_back(head->val);
            head = head->next;
        }
        return res;
    }
    ListNode* addTwoVector(vector<int> v1, vector<int> v2) {
        ListNode *dummy = new ListNode(0), *node = NULL;
        int i = v1.size() - 1, j = v2.size() - 1, sum = 0;
        while (j >= 0 || i >= 0 || sum) {
            if (i >= 0) sum += v1[i--];
            if (j >= 0) sum += v2[j--];
            node = new ListNode(sum % 10);
            sum /= 10;
            node->next = dummy->next;
            dummy->next = node;
        }
        return dummy->next;
    }
public:
    ListNode* addTwoNumbers(ListNode *l1, ListNode *l2) {
        return addTwoVector(convertToVector(l1), convertToVector(l2));
    }
};






