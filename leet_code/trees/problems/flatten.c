/*

Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
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
             
*/             




class Solution {
public:
    void flatten(TreeNode *root) {
        while (root){
            if (root->left){
                TreeNode* pre=root->left;
                while (pre->right){pre = pre->right;}
                pre->right = root->right;
                root->right = root->left;
                root->left = NULL;
            }
            root=root->right;
        }
    }
};
