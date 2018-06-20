/*
Given a binary tree, find the length of the longest path where each node in the path 
has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2


*/

class Solution {
    int ans;
public:
    int longestUnivaluePath(TreeNode* root) 
    {
        int ans = 0;
        findPath(root, ans);
        return ans;
    }
    
    int findPath(TreeNode *root, int &ans)
    {
        if(!root) return 0;
        
        int leftSide = findPath(root->left, ans);
        int rightSide = findPath(root->right, ans);
        int resl = 0;
        int resr = 0;
        if (root->left && root->left->val == root->val)
        {
            resl = leftSide + 1;
        }
        
        if (root->right && root->right->val == root->val)
        {
            resr = rightSide + 1;
        }
        //Can you reason out why we are not using ls and rs
        // and using resr and resl
        ans = max(ans, resl + resr);
        return max(resl, resr);
    }
};
