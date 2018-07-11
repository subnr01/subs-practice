/*
Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree 
so that all its elements lies in [L, R] (R >= L). You might need to change the root 
of the tree, so the result should return the new root of the trimmed binary search tree.

Example 1:
Input: 
    1
   / \
  0   2

  L = 1
  R = 2

Output: 
    1
      \
       2
Example 2:
Input: 
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output: 
      3
     / 
   2   
  /
 1

*/

class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R, bool top = true) {
    if (!root)
        return root;
    root->left = trimBST(root->left, L, R, false);
    root->right = trimBST(root->right, L, R, false);
    if (root->val >= L && root->val <= R)
        return root;
    auto result = root->val < L ? root->right : root->left;
    //if (!top)
    delete root;
    return result;
}
};


