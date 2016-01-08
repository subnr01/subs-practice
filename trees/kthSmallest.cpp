/*

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note: 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and 
you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

*/

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int elem;
        helper(root, &k, &elem);
        return elem;
    }
    
    void helper(TreeNode *root, int *k, int *elem) {
        if (!root) {
            return;
        }
        
        if (*k > 0) {
            helper(root->left, k, elem);
            --*k;
            if (*k == 0) {
                *elem = root->val;
                return;
            }
            helper(root->right, k, elem);
        }
        
    }
};
