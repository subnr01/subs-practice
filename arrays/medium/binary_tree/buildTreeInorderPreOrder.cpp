/*
Given preorder and inorder traversal of a tree, construct the binary tree.
*/

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        size_t in_sz = inorder.size() - 1;
        int mid = 0;
        return build (preorder, inorder, 0, in_sz, mid);
        
    }
    
    TreeNode *build (vector<int>& preorder, vector<int>& inorder, int is, int ie, int& mid)
    {
        if (is > ie) {
            return NULL;
        }
        
        TreeNode *root = new TreeNode(preorder[mid]);
        mid++;
        int pos = -1;
        // you have sent (size - 1) and hence
        // make sure you have the right comparison
        for (int i = 0; i <= ie; i++)
        {
            if (inorder[i] == root->val) {
                pos = i;
                break;
            }
        }
        
        root->left = build (preorder, inorder, is, pos - 1, mid);
        root->right = build (preorder, inorder, pos + 1, ie, mid);
        
        return root;
    }
};
