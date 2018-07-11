/*
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following is not:
    1
   / \
  2   2
   \   \
   3    3



*/

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) {
            return true;
        }
        
        return check(root->left, root->right);
    }
    
    bool check (TreeNode *nleft, TreeNode *nright)
    {
        if(!nleft || !nright)
        {
            return nleft == nright;
        }
        
        return (nleft->val == nright->val) &&
                check(nleft->left, nright->right) &&
                check(nleft->right, nright->left);
    }
};
