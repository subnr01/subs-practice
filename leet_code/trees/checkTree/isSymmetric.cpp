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
    bool isSymmetric(TreeNode *root) {
        return isSymmetric_1(root);
    }
    
    bool isSymmetric_1(TreeNode *root) {
        if (!root) return true;
        return isSymmetricRe(root->left, root->right);
    }

    bool isSymmetricRe(TreeNode *t1, TreeNode *t2)
    {
        if (!t1 && !t2) return true;
        if (!t1 || !t2 || t1->val != t2->val) return false;
        return isSymmetricRe(t1->left, t2->right) &&
               isSymmetricRe(t1->right, t2->left);
    }

    bool isSymmetric_2(TreeNode *root) {
        if (!root) return true;
        queue<TreeNode *> q;
        q.push(root->left);
        q.push(root->right);
        while (!q.empty())
        {
            TreeNode *t1 = q.front(); q.pop();
            TreeNode *t2 = q.front(); q.pop();
            if (!t1 && !t2) continue;
            if (!t1 || !t2 || t1->val != t2->val)
                return false;
            q.push(t1->left);
            q.push(t2->right);
            q.push(t1->right);
            q.push(t2->left);
        }
        return true;
    }
};
