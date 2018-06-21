/*
Given a binary tree, find the length of the longest consecutive sequence path.

Example 1:

Input:

   1
    \
     3
    / \
   2   4
        \
         5

Output: 3

Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
Example 2:

Input:

   2
    \
     3
    / 
   2    
  / 
 1

Output: 2 

Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return 2.

*/

class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        int maxlength = 0;
        int length = 1;
        if (!root) {
            return 0;
        }
        
        TreeNode *parent = NULL;
        
        dfs(root, parent, maxlength, length);
        return maxlength;
    }
    
    void dfs(TreeNode *root, TreeNode *parent, int &maxlength, int length)
    {
        if (!root) {
            return;
        }
        if (parent) {
         length = (root->val) == parent->val + 1 ? length + 1: 1;
        }
        
        maxlength = max(maxlength, length);
        parent = root;
        
        dfs(root->left, parent, maxlength, length);
        dfs(root->right, parent, maxlength, length);
        return;
    }
};
