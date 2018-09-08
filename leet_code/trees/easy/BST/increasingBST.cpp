/*

Given a tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree,
and every node has no left child and only 1 right child.

Example 1:
Input: [5,3,6,2,4,null,8,1,null,null,null,7,9]

       5
      / \
    3    6
   / \    \
  2   4    8
 /        / \ 
1        7   9

Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

 1
  \
   2
    \
     3
      \
       4
        \
         5
          \
           6
            \
             7
              \
               8
                \
                 9  
 */

/*
A simple solution where we adopt the reverse inorder strategy.
We will have a prev pointer that will point to the prev node in
the reverse inorder flow.
We will traverse the tree from the right and set the root->right 
to the prev pointer. This actually has no effect on the right children,
as root->right is already pointing to the right children.

However when we move into the left subtree, we will get to the rightmost
child and point its right to the root, from then on the process continues
with the right pointer of the parent being unchanged, but the recursive
call going downwards and resetting the right pointers to point to 
their parents.

*/

class Solution {
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode *newRoot = NULL;
        revInorder(root, newRoot);
        return newRoot;
    }
    
    void revInorder(TreeNode *root, TreeNode *&curr)
    {
        if (!root) {
            return;
        }
        
        revInorder(root->right, curr);
        root->right = curr;
        curr = root;
        revInorder(root->left, curr);
        root->left = NULL;
    }
};
