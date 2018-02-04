/*
Given a complete binary tree, count the number of nodes.

*/

class Solution {

public:

    int countNodes(TreeNode* root) {

        if(!root) return 0;

        int hl=0, hr=0;

        TreeNode *l=root, *r=root;

        while(l) {hl++;l=l->left;}

        while(r) {hr++;r=r->right;}

        if(hl==hr) return pow(2,hl)-1;

        return 1+countNodes(root->left)+countNodes(root->right);

    }

};

//Using binary search
int countNodes(TreeNode* root) {
    if(!root) return 0;
    TreeNode *temp = root;
    int height = 0, count = 0, level;
    while(temp) {
        temp = temp->left;
        height ++;
    }
    temp = root;
    level = height - 2;
    while(level >= 0) {
        TreeNode *left = temp->left;
        for(int i = 0;i < level;i ++) {
            left = left->right;
        }
        if(left) {
            temp = temp->right;
            count += (1 << level);
        } else temp = temp->left;
        level --;
    }
    if(temp) count ++;
    return (1 << (height - 1)) + count - 1;
}
