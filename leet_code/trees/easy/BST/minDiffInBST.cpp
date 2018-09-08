/*
Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of 
any two different nodes in the tree.

Example :

Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.

The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \    
    1   3  

while the minimum difference in this tree is 1, it occurs between node 1 and node 2, also between node 3 and 
node 2


*/


/*
This problem is same as the other node, except for the case that here we have
negative values while the other one considered only non-negative values
*/

class Solution {
public:
   void inorderTraverse(TreeNode* root, int& val, int& min_dif) 
   {
       if (root->left != NULL) {
           inorderTraverse(root->left, val, min_dif);
       }
       
       if (val >= 0) {
           min_dif = min(min_dif, abs(root->val - val));
       }
       
       val = root->val;
       
       if (root->right != NULL) {
           inorderTraverse(root->right, val, min_dif);
       }
   }
   
   int minDiffInBST(TreeNode* root) 
   {
       auto min_dif = INT_MAX, val = -1;
       inorderTraverse(root, val, min_dif);
       return min_dif;
   }
};
