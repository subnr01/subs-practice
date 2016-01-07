/*


Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree {3,9,20,#,#,15,7},
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]


*/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
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
        return res;
        
    }

    /*
    Level order using DFS
    */

    vector<vector<int>> levelOrder_dfs(TreeNode *root) {
        vector<vector<int>> res;
        levelOrderRe(root, 0, res);
        return res;
    }

    /* 
     Important thing to note here
     how a vector is added to the vector of vectors
     dynamically.
     How vector is indexed as a subscript
     Using DFS approach, vector at every level
     is filled one by one.
     */

    void levelOrderRe(TreeNode *node, int level, vector<vector<int>> &res)
    {
        if (!node) return;
        if (res.size() <= level) res.push_back(vector<int>());
        res[level].push_back(node->val);
        levelOrderRe(node->left, level + 1, res);
        levelOrderRe(node->right, level + 1, res);
    }
};
