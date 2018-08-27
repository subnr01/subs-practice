/*

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
*/


/*
Solution
*/

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) return new TreeNode(head->val);
        ListNode* mid = findMid(head);
        TreeNode* root = new TreeNode(mid->val);
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(mid->next);
        return root;
    }
    
    ListNode* findMid(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *prev = nullptr, *slow = head, *fast = head;
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = nullptr; // have to break the linked list apart
        return slow;
    }
};
