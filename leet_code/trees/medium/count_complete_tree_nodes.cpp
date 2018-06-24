/*
Given a complete binary tree, count the number of nodes.

A complete binary tree where it is completely filled at every level except
the last level where it is left alligned
*/

class Solution {
public:
    int countNodes(TreeNode* root) 
    {
        int nodes = 0;
        int h = height(root);
        
        while (root)
        {
            if (height(root->right) == h - 1)
            {
                // root + nodes in the left subtree
                nodes += 1 << h;
                root = root->right;
            } else {
                // root + nodes in the right subtree
                nodes += 1 << (h - 1);
                root = root->left;
            }
            h--;
        }
        return nodes;
        
    }
    
    int height (TreeNode *root)
    {
        // see how we return -1 on null here
        return root == NULL ? -1 : 1 + height(root->left);
    }
};
