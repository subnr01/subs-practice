/*
Given a binary tree where every node has a unique value, and a target key k, find the value 
of the nearest leaf node to target k in the tree.

Here, nearest to a leaf means the least number of edges 
travelled on the binary tree to reach any leaf of the tree. Also, a node is called a leaf if it has no children.

Example 1:

Input:
root = [1, 3, 2], k = 1
Diagram of binary tree:
          1
         / \
        3   2

Output: 2 (or 3)

Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.

Example 2:

Input:
root = [1], k = 1
Output: 1

Explanation: The nearest leaf node is the root node itself.
Example 3:

Input:
root = [1,2,3,4,null,null,null,5,null,6], k = 2
Diagram of binary tree:
             1
            / \
           2   3
          /
         4
        /
       5
      /
     6

Output: 3
Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
*/


class Solution {
public:
    int findClosestLeaf(TreeNode* root, int k) {
        if (!root) return 0;
        if (!root->left && !root->right) return k;
        G.clear(); G.resize(1001); go(root);
        return bfs(root->val,k);
    }
private:
    vector<vector<int>> G;
    void go(TreeNode* root){
        if (root->left){ link(root,root->left); go(root->left); }
        if (root->right){ link(root,root->right); go(root->right); }
    }
    void link(TreeNode* parent, TreeNode* child){
        G[parent->val].push_back(child->val);
        G[child->val].push_back(parent->val);
    }
    int bfs(int root, int target){
        unordered_set<int> v({target});
        queue<int> q({target});
        while (!q.empty()){
            auto curr=q.front(); q.pop();
            if (curr!=root && G[curr].size()==1) return curr; // leaf node has 1 neighbor (except root)
            for (auto nei: G[curr])
                if (v.find(nei)==v.end()){ q.push(nei); v.insert(nei); }
        }
        return -1;
    }
};






