/*

 Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left 
 to right, then right to left for the next level and alternate between).
 For example:
 Given binary tree {3,9,20,#,#,15,7},
     3
    / \
   9  20
  / \
 15  7
 return its zigzag level order traversal as:
 [
  [3],
  [20,9],
  [15,7]
 ]
 Solution: 1. Queue + reverse.
           2. Two stacks.
           3. Vector. Contributed by yinlinglin.
 */

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

vector<vector<int> > zigzagLevelOrder(TreeNode* root) {
    if (root == NULL) {
        return vector<vector<int> > ();
    }
    vector<vector<int> > result;

    queue<TreeNode*> nodesQueue;
    nodesQueue.push(root);
    bool leftToRight = true;

    while ( !nodesQueue.empty()) {
        int size = nodesQueue.size();
        vector<int> row(size);
        for (int i = 0; i < size; i++) {
            TreeNode* node = nodesQueue.front();
            nodesQueue.pop();

            // find position to fill node's value
            int index = (leftToRight) ? i : (size - 1 - i);

            row[index] = node->val;
            if (node->left) {
                nodesQueue.push(node->left);
            }
            if (node->right) {
                nodesQueue.push(node->right);
            }
        }
        // after this level
        leftToRight = !leftToRight;
        result.push_back(row);
    }
    return result;
}
    
    // Solution 2: Two stacks.
    vector<vector<int>> zigzagLevelOrder_2(TreeNode *root) {
        vector<vector<int>> res;
        if (!root) return res;
        stack<TreeNode *> stk[2];
        bool left2right = true;
        int cur = 1, last = 0;
        stk[last].push(root);
        vector<int> level;
        while (!stk[last].empty())
        {
            TreeNode *node = stk[last].top(); 
            stk[last].pop();
            if (node)
            {
                level.push_back(node->val);
                if (left2right)
                {
                    stk[cur].push(node->left);
                    stk[cur].push(node->right);
                }
                else
                {
                    stk[cur].push(node->right);
                    stk[cur].push(node->left);
                }
            }
            if (stk[last].empty())
            {
                if (!level.empty())
                    res.push_back(level);
                level.clear();
                swap(cur, last);
                left2right = !left2right;
            }
        }
        return res;
    }
    
    // Solution 3: Vector. Contributed by yinlinglin.
    // Compared to solution 1&2, this solution costs a little more space.
    // This solution uses only one single vector instead of two stacks in solution 2.
    vector<vector<int>> zigzagLevelOrder_3(TreeNode *root) {
        vector<vector<int>> result;
        if(!root) return result;
        vector<TreeNode*> v;
        v.push_back(root);
        bool left2right = true;
        int begin = 0, end = 0;
        while(begin <= end)
        {
            vector<int> row;
            for (int i = end; i >= begin; --i)
            {
                if (!v[i]) continue;
                row.push_back(v[i]->val);
                if(left2right)
                {
                    v.push_back(v[i]->left);
                    v.push_back(v[i]->right);
                }
                else
                {
                    v.push_back(v[i]->right);
                    v.push_back(v[i]->left);
                }
            }
            if (!row.empty())
                result.push_back(row);
            begin = end + 1;
            end = v.size() - 1;
            left2right = !left2right;
        }
        return result;
    }
};
