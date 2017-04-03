/*

Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any
node in the tree along the parent-child connections. The path does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
     
Return 6.

*/


int maxPathSum(TreeNode *root) {
    int maxPath = INT_MIN;
    dfsMaxPath(root, maxPath);
    return maxPath;
}

int dfsMaxPath(TreeNode *root, int &maxPath) {
    if (!root) return 0;
    // the significance of 0 enables us
    // to ignore negative values and
    // pass root->val as is of it is the max
    int l = max(0, dfsMaxPath(root->left, maxPath));
    int r = max(0, dfsMaxPath(root->right, maxPath));
    maxPath = max(maxPath, l + r + root->val);
    return root->val + max(l, r);
}


//Another solution
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
