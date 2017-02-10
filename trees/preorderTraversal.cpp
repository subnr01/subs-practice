/*

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].

*/


class Solution {
public:
    
 vector<int> preorderTraversal(TreeNode *root) {
    if (root==NULL) {
        return vector<int>();
    }
    vector<int> result;
    stack<TreeNode *> treeStack;
    treeStack.push(root);
    while (!treeStack.empty()) {
        TreeNode *temp = treeStack.top();
        result.push_back(temp->val);
        treeStack.pop();
        if (temp->right!=NULL) {
            treeStack.push(temp->right);
        }
        if (temp->left!=NULL) {
            treeStack.push(temp->left);
        }
    }
    return result;
    }
};
