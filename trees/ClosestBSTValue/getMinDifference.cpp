https://leetcode.com/problems/minimum-absolute-difference-in-bst/?tab=Description

/*

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).


*/


class Solution {
    int min_dif = INT_MAX, val = -1;
public:
int getMinimumDifference(TreeNode* root) {
    if (root->left != NULL) 
    {
        getMinimumDifference(root->left);
    }
    
    if (val >= 0) {
        min_dif = min(min_dif, root->val - val);
    }
    val = root->val;
    
    if (root->right != NULL) {
        getMinimumDifference(root->right);
    }
    
    return min_dif;
}
};


void inorderTraverse(TreeNode* root, int& val, int& min_dif) {
    if (root->left != NULL) inorderTraverse(root->left, val, min_dif);
    if (val >= 0) min_dif = min(min_dif, root->val - val);
    val = root->val;
    if (root->right != NULL) inorderTraverse(root->right, val, min_dif);
}
int getMinimumDifference(TreeNode* root) {
    auto min_dif = INT_MAX, val = -1;
    inorderTraverse(root, val, min_dif);
    return min_dif;
}

