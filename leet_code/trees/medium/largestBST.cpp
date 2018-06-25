/*

Given a binary tree, find the largest subtree which is a 
Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.


*/

class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {        
        if (!root) return 0;
        unordered_map<TreeNode*, bool> mBST;
        int res = 1;
        getBig(root, mBST, res);
        return res;
    }
    void getBig(TreeNode* root, unordered_map<TreeNode*, bool>& mBST, int& res) {
        if (root) {
            if(isBST(root)) {
                res = max(getSize(root), res);
                return;
            }
            if (isBST(root->left)){
                res = max(res, getSize(root->left));
            }
            if (isBST(root->right)){
                res = max(res, getSize(root->right));
            }
            getBig(root->left, mBST, res);
            getBig(root->right, mBST, res);
        }
    }
    int getSize(TreeNode* root) {        
        if(!root) return 0;        
        return 1 + getSize(root->left) + getSize(root->right);
    }    
    bool isBST(TreeNode* root) {
        TreeNode* prev = NULL;
        return validate(root, prev);
    }
    bool validate(TreeNode* node, TreeNode* &prev) {
        if (node == NULL) return true;
        if (!validate(node->left, prev)) return false;
        if (prev != NULL && prev->val >= node->val) return false;
        prev = node;
        return validate(node->right, prev);
    }
    
};
