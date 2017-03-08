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

What if it is not a BST? (Follow up of the problem) The idea is to put values in a TreeSet and 
then every time we can use O(lgN) time to lookup for the nearest values.

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
