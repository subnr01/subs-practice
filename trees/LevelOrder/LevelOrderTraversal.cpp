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
class Solution{
    public:
vector<vector<int> > levelOrder(TreeNode* root) {
    if (root == NULL) {
        return vector<vector<int> > ();
    }
    vector<vector<int> > result;

    queue<TreeNode*> nodesQueue;
    nodesQueue.push(root);
   // bool leftToRight = true;

    while ( !nodesQueue.empty()) {
        int size = nodesQueue.size();
        vector<int> row (size);
        for (int i = 0; i < size; i++) {
            TreeNode* node = nodesQueue.front();
            nodesQueue.pop();
            row[i] = node->val;
            
            if (node->left) {
                nodesQueue.push(node->left);
            }
            if (node->right) {
                nodesQueue.push(node->right);
            }
        }
        // after this level
        result.push_back(row);
        
    }
    return result;
}
};
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
        if (res.size() == level) res.push_back(vector<int>());
        res[level].push_back(node->val);
        levelOrderRe(node->left, level + 1, res);
        levelOrderRe(node->right, level + 1, res);
    }
};

