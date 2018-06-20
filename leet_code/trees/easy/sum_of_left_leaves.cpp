
/*
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
*/


class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root, bool isLeft = false) {
        
        if (!root) {
            return 0;
        }
        
        if (!root->left && !root->right && isLeft) {
            return root->val;
        }
        
        return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
        
    }
};
