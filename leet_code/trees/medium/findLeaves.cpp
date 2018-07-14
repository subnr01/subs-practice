
/*
Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves,
repeat until the tree is empty.

Example:
Given binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Returns [4, 5, 3], [2], [1].

Explanation:
1. Removing the leaves [4, 5, 3] would result in this tree:

          1
         / 
        2          
2. Now removing the leaf [2] would result in this tree:

          1          
3. Now removing the leaf [1] would result in the empty tree:

          []         
Returns [4, 5, 3], [2], [1].

*/

class Solution {
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        
        vector<vector<int>> res;
        if (!root) {
            return res;
        }
        
        find(root, res);
        return res;
    }
    
    int find(TreeNode *root, vector<vector<int>> &res)
    {
        if (!root) return 0;
        int level = max(find(root->left, res), find(root->right, res)) + 1;
        if(res.size() < level) {
            res.push_back(vector<int>());
        }
        res[level - 1].push_back(root->val);
        return level;
    }
};
