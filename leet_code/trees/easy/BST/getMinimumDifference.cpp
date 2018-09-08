/*
Given a binary search tree with non-negative values, find the minimum absolute difference 
between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
*/

/*
here we have to find the minimum distance between two nodes in the BST.

The easiest solution is to a inorder traversal and get the difference between
the previous and the current nodes and compare the difference on every iteration.
*/
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        long mindiff = INT_MAX;
        TreeNode* prev = nullptr;
        find(root, prev, mindiff);
        return mindiff;
    }
private:
    void find(TreeNode* node, TreeNode*& prev, long& mindiff) {
        if (node->left) { 
            find(node->left, prev, mindiff);
        }

        if (prev != nullptr) {
            mindiff = std::min(mindiff, (long)abs(node->val - prev->val));
        }
        prev = node;

        if (node->right) {
            find(node->right, prev, mindiff);
        }
    }
};
