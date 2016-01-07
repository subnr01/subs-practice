/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

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
        vector<int> level;
        
        TreeNode *curr = root;
         
        if (!root) {
            /* 
             return here as 
             we do not want queue
             to be full of NULLs
             */
            return res;
        }
        
        /* 
         * push the first level
         * intially
         */
        q.push(curr);
        q.push(NULL);
        
        /*
         * How do I know when the current level
         * ends
         */
        while (true) {
            TreeNode *temp = q.front();
            q.pop();

            if ( !temp) {
                /*
                 * every time a NULL is encountered
                 * push the level and clear the level
                 * and push NULL as the delimitor for
                 * the next LEVEL
                 */
                res.push_back(level);
                level.clear();
                /* Cover only the root case */
                if (q.empty()) {
                    break;
                }
                q.push(NULL);
            } else {
                level.push_back(temp->val);
                if ( temp->left) {
                    q.push(temp->left);
                }
                if ( temp->right) {
                    q.push(temp->right);
                }
            }
        }
        /* 
           This is the only difference from the other
           level order problem.
           This problem needs the output to be
           printed from bottom up
        */
        reverse(res.begin(), res.end());
        return res;
        
    }
};
