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


class Solution {
public:
    int minDepth_1(TreeNode* root) {
        
        int mindepth = 0;
        minDepth(root, mindepth, 0);
        return mindepth;
    }
    
    void minDepth(TreeNode *root, int &mindepth, int depth) {
        
        if(!root) {
            return;
        }
        
        depth+=1;
        
        if(!root->left && !root->right) {
            if (mindepth == 0) {
                mindepth = depth;
            } else {
                mindepth = min(mindepth, depth);
            }
            return;
        }
        
        minDepth(root->left, mindepth, depth);
        minDepth(root->right, mindepth, depth);
        
    }
    
    int minDepth(TreeNode *root) {
        if (!root) return 0;
        queue<TreeNode *> q;
        q.push(root);
        q.push(NULL);
        int depth = 1;
        while (true)
        {
            TreeNode *node = q.front();
            q.pop();
            if (!node) {
                depth++;
                q.push(NULL);
            } else {
                if (!node->left && !node->right) return depth;
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
    }
};
