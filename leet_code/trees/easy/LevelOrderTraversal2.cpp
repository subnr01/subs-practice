/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, 
level by level from leaf to root).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
   
return its bottom-up level order traversal as:

[
  [15,7],
  [9,20],
  [3]
]
*/


class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> res;
       
        
        TreeNode *curr = root;
         
        if (!root) {
            return res;
        }
        
        vector<int> level;
        q.push(curr);
        
        while (!q.empty())
        {
            int s = q.size();
            
            for (int i = 0; i < s; i++)
            {
                TreeNode *temp = q.front();
                q.pop();
                level.push_back(temp->val);
                if (temp->left)
                {
                    q.push(temp->left);
                }
                if (temp->right)
                {
                    q.push(temp->right);
                }
            }
            res.push_back(level);
            level.resize(0);
        }
        
        reverse(res.begin(), res.end());
        return res;
        
    }
};
