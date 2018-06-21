/*
We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.

Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

Example 1:
Input: [1,null,0,0,1]
Output: [1,null,0,null,1]
 
Explanation: 
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.

*/


class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) 
    {
       return prune(root)? root: NULL;
    }
    
    bool prune(TreeNode *root)
    {
         if (!root) {
            return false;
        }
        bool left = prune(root->left);
        bool right = prune(root->right);
        
        if (!left)
        {
            root->left = NULL;
        }
        
        if (!right)
        {
            root->right = NULL;
        }
        
        return root->val || left || right;
    }
 };
