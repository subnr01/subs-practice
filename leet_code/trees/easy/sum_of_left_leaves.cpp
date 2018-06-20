
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


int sumOfLeftLeaves(TreeNode* root, bool isleft = false) {
    if (!root) return 0;
    if (!root->left && !root->right) return isleft ? root->val : 0;
    return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
}
