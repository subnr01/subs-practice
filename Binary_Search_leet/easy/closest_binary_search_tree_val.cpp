/*
Given a non-empty binary search tree and a target value, find the value in the
BST that is closest to the target

*/



Recursive:

class Solution {
public:
    void getResult(TreeNode *node, double target, double &result){
        if(!node)return;
        if(abs((double)node->val-target)<abs(target-result))result=(double)node->val;
        if((double)node->val>target)
            getResult(node->left,target,result);
        else if((double)node->val<target)
            getResult(node->right,target,result);
    }
    int closestValue(TreeNode* root, double target) {
        double result=(double)root->val;
        getResult(root,target,result);
        return (int)result;
    }
};
Iterative:

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int result=root->val;
        while(root){
            if((double)root->val==target)return root->val;
            if(abs((double)root->val-target)<abs(result-target))
                result=root->val;
            if(root->val>target)root=root->left;
            else root=root->right;
        }
        return result;
    }
};
