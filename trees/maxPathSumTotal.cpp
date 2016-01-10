/*

Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.

*/


class Solution {
public:
    int findmax(TreeNode* root, int &res){
        if (root == NULL) {
            return 0;
        } else {
            int max_l = findmax(root->left, res);
            int max_r = findmax(root->right, res);
            int max_s = max(max(max_l, max_r) + root->val, root->val);
            int max_top = max(max_s, max_l+max_r+root->val);
            res = max(res, max_top);
            return max_s;
        }
    }
     
    int maxPathSum(TreeNode *root) {
        int res = INT_MIN;
        findmax(root, res);
        return res;
    }
};
