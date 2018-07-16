/*

Given the root node of a binary search tree (BST) and a value to be inserted 
into the tree, insert the value into the BST. Return the root node of the BST after the insertion

*/


class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) {
            root = new TreeNode(val);
            return root;
        }
        
        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        } else {
            root->right = insertIntoBST(root->right, val);
        }
        return root;
    }
};
