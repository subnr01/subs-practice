https://leetcode.com/problems/minimum-absolute-difference-in-bst/?tab=Description

/*

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

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


class Solution {
    int min_dif = INT_MAX, val = -1;
public:
int getMinimumDifference(TreeNode* root) {
    if (root->left != NULL) 
    {
        getMinimumDifference(root->left);
    }
    
    if (val >= 0) {
        min_dif = min(min_dif, root->val - val);
    }
    val = root->val;
    
    if (root->right != NULL) {
        getMinimumDifference(root->right);
    }
    
    return min_dif;
}
};


void inorderTraverse(TreeNode* root, int& val, int& min_dif) {
    if (root->left != NULL) inorderTraverse(root->left, val, min_dif);
    if (val >= 0) min_dif = min(min_dif, root->val - val);
    val = root->val;
    if (root->right != NULL) inorderTraverse(root->right, val, min_dif);
}
int getMinimumDifference(TreeNode* root) {
    auto min_dif = INT_MAX, val = -1;
    inorderTraverse(root, val, min_dif);
    return min_dif;
}


What if it is not a BST? (Follow up of the problem) The idea is to put values in a TreeSet and then every time we can use O(lgN) time to lookup for the nearest values.

Solution 2 - Pre-Order traverse, time complexity O(NlgN), space complexity O(N).

public class Solution {
    TreeSet<Integer> set = new TreeSet<>();
    int min = Integer.MAX_VALUE;
    
    public int getMinimumDifference(TreeNode root) {
        if (root == null) return min;
        
        if (!set.isEmpty()) {
            if (set.floor(root.val) != null) {
                min = Math.min(min, Math.abs(root.val - set.floor(root.val)));
            }
            if (set.ceiling(root.val) != null) {
                min = Math.min(min, Math.abs(root.val - set.ceiling(root.val)));
            }
        }
        
        set.add(root.val);
        
        getMinimumDifference(root.left);
        getMinimumDifference(root.right);
        
        return min;
    }
}
