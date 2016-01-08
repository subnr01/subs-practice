/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.


*/





class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST_recur(root, LONG_MIN, LONG_MAX);
    }
    
    bool isValidBST_recur(TreeNode *root, long min, long max) {
        if (!root) {
            return true;
        }
        
        if (root->val <= min || root->val >= max) {
            return false;
        }
        
        return isValidBST_recur(root->left, min, root->val) &&
                isValidBST_recur(root->right, root->val, max);
        
    }

};
