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

//O(n) solution
class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {
        int res = 0, mn = INT_MIN, mx = INT_MAX;
        isValidBST(root, mn, mx, res);
        return res;
    }
    void isValidBST(TreeNode *root, int &mn, int &mx, int &res) {
        if (!root) return;
        int left_n = 0, right_n = 0, left_mn = INT_MIN;
        int right_mn = INT_MIN, left_mx = INT_MAX, right_mx = INT_MAX;
        isValidBST(root->left, left_mn, left_mx, left_n);
        isValidBST(root->right, right_mn, right_mx, right_n);
        if ((!root->left || root->val > left_mx) && (!root->right || root->val < right_mn)) {
            res = left_n + right_n + 1;
            mn = root->left ? left_mn : root->val;
            mx = root->right ? right_mx : root->val;
        } else res = max(left_n, right_n);
    }
};

