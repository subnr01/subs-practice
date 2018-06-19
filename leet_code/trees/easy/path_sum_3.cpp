

/*
You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent
nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

*/


class Solution {
    int m_ret{0};
public:
    int pathSum(TreeNode* root, int sum) {
        if(!root)
            return 0;

        dfs(root, sum);
        pathSum(root->left, sum);
        pathSum(root->right, sum);
        return m_ret;
    }

    inline void dfs(TreeNode *root, int sum) {
        if(!root)
            return;

        int remain = sum - root->val;
        if(remain == 0) {
            ++m_ret;
        }
        /* if remain==0, we have to consider some leaves' value are negivate */
        dfs(root->left, remain);
        dfs(root->right, remain);
        
    }
};

//Really fast one using map
class Solution {
 public:
  unordered_map<int, int> mp;
  int ans = 0;

  void dfs(TreeNode* v, int now, int sum) {
    if (v == NULL) return;
    now += v->val;
    ans += mp[now - sum];
    ++mp[now];
    dfs(v->left, now, sum);
    dfs(v->right, now, sum);
    --mp[now];
  }
  int pathSum(TreeNode* root, int sum) {
    mp[0] = 1;
    dfs(root, 0, sum);
    return ans;
  }
};
