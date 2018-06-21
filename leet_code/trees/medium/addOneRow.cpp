/*

Given the root of a binary tree, then value v and depth d, you need to add a row of
nodes with value v at the given depth d. The root node is at depth 1.

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1



*/

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            TreeNode *node = new TreeNode(v);
            node->left = root;
            return node;
        }
        
        int level = 2;
        return addRow(root, v, d, level);
    }
    
    TreeNode *addRow(TreeNode *root, int val, int d, int level)
    {
        if (!root) 
        {
            return NULL;
        }
        
        if (d == level)
        {
            TreeNode *newLeft = new TreeNode(val);
            TreeNode *newRight = new TreeNode(val);
            
            TreeNode *oldLeft = root->left;
            TreeNode *oldRight = root->right;
            
            root->left = newLeft;
            root->right = newRight;
            
            newLeft->left = oldLeft;
            newRight->right = oldRight;
            return root;
        }
        
        root->left = addRow(root->left, val, d, level + 1);
        root->right = addRow(root->right, val, d, level + 1);
        return root;
        
    }
};
