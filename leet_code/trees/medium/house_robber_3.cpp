/*
After a tour, the smart thief realized that "all houses in this place forms a binary tree". 
It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
     3
    / \
   2   3
    \   \ 
     3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
     3
    / \
   4   5
  / \   \ 
 1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9.

*/

class Solution {
public:
    int rob(TreeNode* root) {
        return robDFS(root).second;
    }
    pair<int, int> robDFS(TreeNode* node){
        if( !node) return make_pair(0,0);
        auto l = robDFS(node->left);
        auto r = robDFS(node->right);
        int f1 = l.second + r.second;        // Do not rob node
        int f2 = max(f1, l.first + r.first + node->val);  // rob node if necessary
        return make_pair(f1, f2);
    }
};
