
/*
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Example 1:

Input: root = [2,1,3], p = 1

  2
 / \
1   3

Output: 2
Example 2:

Input: root = [5,3,6,2,4,null,null,1], p = 6

      5
     / \
    3   6
   / \
  2   4
 /   
1

Output: null

*/
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode *cand = NULL;
        
        while (root)
        {
            if (root->val > p->val) {
                cand = root;
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return cand;
    }
};



TreeNode* predecessor(TreeNode* root, TreeNode* p) {
    TreeNode* candidate = NULL;
    while (root)
        root = (root->val < p->val) ? (candidate = root)->right : root->left;
    return candidate;
}

 
