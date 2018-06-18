/*

Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]

*/



class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) 
    {
        string path;
        vector<string> res;
        if (!root)
        {
            return res;
        }
        findPaths(root, path, res);
        return res;
      
    }
    
    void findPaths(TreeNode *root, string path, vector<string> &res)
    {
        
        path += to_string(root->val);
       
        if (!root->left && !root->right) {
            res.push_back(path);
            return;
        }
        
        if (root->left)
        {
            findPaths(root->left, path + "->", res);
        }
        
        if (root->right)
        {
            findPaths(root->right, path + "->", res);
        }
        
        return;
    }
};
