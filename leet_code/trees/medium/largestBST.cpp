/*

Given a binary tree, find the largest subtree which is a 
Binary Search Tree (BST), where largest means subtree with largest number of nodes in it.


*/

class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {
        int res = 0, mn = INT_MIN, mx = INT_MAX;
        isValidBST(root, mn, mx, res);
        return res;
    }
    void isValidBST(TreeNode *root, int &mn, int &mx, int &res) {
        if (!root) {
            return;
        }
        
        int left_nodes = 0;
        int right_nodes = 0;
       
        int left_mn = INT_MIN;
        int right_mn = INT_MIN; 
        
        int left_mx = INT_MAX; 
        int right_mx = INT_MAX;
       
        isValidBST(root->left, left_mn, left_mx, left_nodes);
        isValidBST(root->right, right_mn, right_mx, right_nodes);
        
        if ((!root->left || root->val > left_mx) && (!root->right || root->val < right_mn)) {
            res = left_nodes + right_nodes + 1;
            mn = root->left ? left_mn : root->val;
            mx = root->right ? right_mx : root->val;
        } else { 
            res = max(left_nodes, right_nodes);
        }
    }
};
