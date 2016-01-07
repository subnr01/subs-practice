
/*
Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},

  1
    \
     2
    /
   3
return [1,3,2].

Note: Recursive solution is trivial, could you do it iteratively?

*/


class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        TreeNode *curr = NULL;
        stack<TreeNode*> s;
        vector<int> inorder;
        curr = root;
        
        /* 
         * Need to check stack is not empty
         * as  if the input is only
         * root, then current will be null
         * but stack will have one element
         * that will not be traversed.
         */
        while (curr || !s.empty()) {
            if(curr) {
                s.push(curr);
                curr = curr->left;
            } else {
                inorder.push_back(s.top()->val);
                curr = s.top()->right;
                s.pop();
            }
        }
        return inorder;
    }
};
