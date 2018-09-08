/*
Given a binary search tree with non-negative values, find the minimum absolute difference 
between values of any two nodes.

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

/*
here we have to find the minimum distance between two nodes in the BST.

The easiest solution is to a inorder traversal and get the difference between
the previous and the current nodes and compare the difference on every iteration.
*/
class Solution {
public:
   void inorderTraverse(TreeNode* root, int& val, int& min_dif) 
   {
       if (root->left != NULL) {
           inorderTraverse(root->left, val, min_dif);
       }
       
       if (val >= 0) {
           min_dif = min(min_dif, root->val - val);
       }
       
       val = root->val;
       
       if (root->right != NULL) {
           inorderTraverse(root->right, val, min_dif);
       }
   }
   
   int getMinimumDifference(TreeNode* root) 
   {
       auto min_dif = INT_MAX, val = -1;
       inorderTraverse(root, val, min_dif);
       return min_dif;
   }
};


