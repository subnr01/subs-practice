/*

Given inorder and postorder traversal of a tree, construct the binary tree.

*/

class Solution {
public:
   TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    int post_order = postorder.size() - 1;
    return create(inorder, postorder, 0, inorder.size() - 1, &post_order);
}

TreeNode* create(vector<int> &inorder, vector<int> &postorder, int is, int ie, int *pe){
    
    if(is > ie) {
        return nullptr;
    }
    TreeNode* node = new TreeNode(postorder[*pe]);
    (*pe)--;

    
    int pos;
    for(int i = is; i <= ie; i++){
        if(inorder[i] == node->val){
            pos = i;
            break;
        }
    }
   node->left = create(inorder, postorder, is, pos - 1, pe); 
   node->right = create(inorder, postorder, pos + 1, ie, pe);
    
    
    return node;
}
};
