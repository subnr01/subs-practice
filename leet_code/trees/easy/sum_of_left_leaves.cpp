
/*
Find the sum of all left leaves in a given binary tree.

*/


int sumOfLeftLeaves(TreeNode* root, bool isleft = false) {
    if (!root) return 0;
    if (!root->left && !root->right) return isleft ? root->val : 0;
    return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
}
