/*
Given a binary tree, write a function to get the maximum width of the given tree. The width of a tree is the maximum width among all levels.
The binary tree has the same structure as a full binary tree, but some nodes are null.

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).




*/

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        vector<int> lefts; // left most nodes at each level;
        return dfs(root, 1, 0, lefts);
    }
private:
    int dfs(TreeNode* n, int id, int d, vector<int>& lefts) { // d : depth
        if (!n) return 0;
        if (d >= lefts.size()) {
            lefts.push_back(id);  // add left most node
        }
        
        int left = dfs(n->left, id * 2, d + 1, lefts);
        int right = dfs(n->right, id * 2 + 1, d + 1, lefts);
        return max(id + 1 - lefts[d], max(left , right));
    }
};
