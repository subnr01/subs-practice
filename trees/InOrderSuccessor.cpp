

Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* candidate = NULL;
    while (root)
        root = (root->val > p->val) ? (candidate = root)->left : root->right;
    return candidate;
}



TreeNode* predecessor(TreeNode* root, TreeNode* p) {
    TreeNode* candidate = NULL;
    while (root)
        root = (root->val < p->val) ? (candidate = root)->right : root->left;
    return candidate;
}

 
