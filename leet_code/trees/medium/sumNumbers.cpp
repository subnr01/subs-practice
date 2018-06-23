
/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.

*/


class Solution {
public:
    int sumNumbers(TreeNode* root) {
        int sum = 0;
        sumNumbers_1(root, &sum, 0);
        return sum;        
    }
    
    void sumNumbers_1(TreeNode* root, int *sum, int val) {
        if (!root) {
            return;
        }
        
        val = 10*val + root->val;
        
        if(!root->left && !root->right) {
            *sum += val;
            return;
        }
        
        sumNumbers_1(root->left, sum, val);
        sumNumbers_1(root->right, sum, val);
    }
};
