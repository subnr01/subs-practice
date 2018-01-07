
/*
Given inorder and postorder traversal of a tree, construct the binary tree.
*/


class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        size_t n = inorder.size() - 1;
        int pe = postorder.size() - 1;
        
        return build (inorder, postorder, 0, n, pe);
        
    }
    
    TreeNode* build (vector<int>& inorder, vector<int>& postorder, int is, int ie, int& pe)
    {
        if (is > ie) 
        {
            return NULL;
        }
        
        TreeNode* root = new TreeNode (postorder[pe]);
        --pe;
        int pos = -1;
        for ( int i = is; i <= ie; i++) 
        {
            if (inorder[i] == root->val) {
                pos = i;
                break;
            }
        }
        // be careful with "is" and "ie" here.
        root->right = build (inorder, postorder, pos + 1, ie, pe);
        root->left = build (inorder, postorder, is, pos - 1, pe);
        return root;
    }
};
