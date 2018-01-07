/*
Given preorder and inorder traversal of a tree, construct the binary tree.
*/

class Solution {
public:
    int findId(int n, vector<int> &inorder){
        for (int i=0;i<inorder.size();i++){
            if (inorder[i] == n) return i;
        }
    }
 
    TreeNode* bst(vector<int> &preorder, int &mid, vector<int> &inorder, int st, int ed){
        if (st>ed ){
            return NULL;
        }
        TreeNode* root = new TreeNode(preorder[mid]);
        int idx = findId(preorder[mid], inorder);
        mid++;
        root->left = bst(preorder, mid, inorder, st, idx-1);
        root->right = bst(preorder, mid, inorder, idx+1, ed);
        return root;
    }
     
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        int mid = 0;
      
        return bst(preorder, mid, inorder, 0, inorder.size()-1);
    }
};
