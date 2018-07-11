/*

We are given a binary tree (with root node root), a target node, and an integer value K.

Return a list of the values of all nodes that have a distance K from the target node.  
The answer can be returned in any order.

Example 1:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

Output: [7,4,1]

Explanation: 
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.

*/


class Solution {
    vector<int> res;
    TreeNode* tar;
    int K;
    
    void add_subtree(TreeNode* cur, int d) {
        if (!cur)
            return;
        if (d == K) {
            res.push_back(cur->val);
            return;
        }
        add_subtree(cur->left, d + 1);
        add_subtree(cur->right, d + 1);
    }
    
    uint32_t dfs(TreeNode* cur) {
        if (!cur)
            return -1;
        if(tar ==  cur) {
            add_subtree(cur, 0);
            return 1;
        }

        auto l = dfs(cur->left);
        auto r = dfs(cur->right);
        if (l == K || r == K) {
            res.push_back(cur->val);
            return -1;
        } else if (l !=-1) {
            add_subtree(cur->right, l + 1);
            return l + 1;
        }
        else if (r != -1) {
            add_subtree(cur->left,  r + 1);
            return r + 1;
        }
        return -1;
    }
    
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        tar = target;
        this->K = K;
        dfs(root);
        return res;
    }
};
