/*
Given preorder and inorder traversal of a tree, construct the binary tree.
*/

class Solution {
public:
 TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    return create(0, 0, inorder.size() - 1, preorder, inorder); 
}

TreeNode *create(int preStart, int inStart, int inEnd, vector<int>& preorder, vector<int>& inorder) {

    if (preStart > preorder.size() -1 || inStart > inEnd)
    {
        return NULL;
    }
    
    TreeNode *root = new TreeNode(preorder[preStart]);
    int inIndex = 0; // Index of current root in inorder
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == root->val) {
            inIndex = i;
        }
    }
    
    root->left = create(preStart + 1, inStart, inIndex - 1, preorder, inorder);
    root->right = create(preStart + inIndex - inStart + 1, inIndex + 1, inEnd, preorder, inorder);
    return root;
}
};
