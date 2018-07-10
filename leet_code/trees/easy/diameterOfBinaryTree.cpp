/*
Given a binary tree, you need to compute the length of the diameter of the tree. 
The diameter of a binary tree is the length of the longest path between any two nodes
in a tree. This path may or may not pass through the root.

Example:
Given a binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

*/


class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxD = 0;
        findDiameter(root, maxD);
        return maxD;
        
    }
    
    int findDiameter(TreeNode *root, int &maxD)
    {
        if (!root) {
            return 0;
        }
              
        int ld = findDiameter(root->left, maxD);
        int rd = findDiameter(root->right, maxD);
        
        //WE are not adding 1 here, since this counts both the nodes.
        //not adding 1 here counters by subtracting the root node.
        maxD = max(maxD, rd + ld);
        return max(rd + 1, ld + 1);
    }
};
