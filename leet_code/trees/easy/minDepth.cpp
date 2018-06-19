/*
Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.

*/


//BFS
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
        {
            return 0;
        }
        
        queue<TreeNode *> q;
        int depth = 0;
        q.push(root);
        
        while(!q.empty())
        {
            int s = q.size();
            depth++;
            for (int i = 0; i < s; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                
                if (!node->left && !node->right) {
                    return depth;
                }
                
                
                if(node->left) {
                    q.push(node->left);
                }
                
                if(node->right) {
                    q.push(node->right);
                }
            }
        }
        return depth;
        
    }
};


//DFS
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        int ans = INT_MAX;
        int depth = 0;
        findminDepth(root, ans, depth);
        return ans;

    }
    
    void findminDepth(TreeNode *root, int &ans, int depth)
    {
        if (!root) {
            return;
        }
        
        depth++;
        
        if (!root->left && !root->right) {
            ans = min(ans, depth);
        }
        
        findminDepth(root->left, ans, depth);
        findminDepth(root->right, ans, depth);
        
    }
};
