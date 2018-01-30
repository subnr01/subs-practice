/*

Binary Tree Vertical Order Traversal

Given a binary tree, return the vertical order traversal of its nodes' values. 
(ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples:

Given binary tree [3,9,20,null,null,15,7],
   3
  /\
 /  \
 9  20
    /\
   /  \
  15   7
return its vertical order traversal as:
[
  [9],
  [3,15],
  [20],
  [7]
]
Given binary tree [3,9,8,4,0,1,7],
     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
return its vertical order traversal as:
[
  [4],
  [9],
  [3,0,1],
  [8],
  [7]
]
Given binary tree [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5),
     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2
return its vertical order traversal as:
[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]

*/

//hash table and queue
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int> > res;
        if(!root) return res;
        
        map<int, vector<int> > m; 
        queue<pair<int, TreeNode* > > q;
        q.push({0, root});
        
        while(!q.empty()){
            auto t = q.front(); q.pop();
            m[t.first].push_back(t.second -> val);
            if(t.second -> left) q.push({t.first - 1, t.second -> left});
            if(t.second -> right) q.push({t.first + 1, t.second -> right});
        }
        
        for(auto it : m){
            res.push_back(it.second);
        }
        return res;
    }
};


//recursion
class Solution {
public:
    vector<vector<int>> verticalOrder2(TreeNode* root) {
        vector<vector<int>> res;
        helper(root, 0, res);
        return res;
    }
    
    void helper(TreeNode* root, int idx, vector<vector<int>>& res) {
        if (!root) return;
        if (idx == res.size()) {
            res.push_back(vector<int>(1, root->val));
        }
        else if (idx == -1) {
            res.insert(res.begin(), vector<int>(1, root->val));
            idx = 0;
        }
        else {
            res[idx].push_back(root->val);
        }
        helper(root->left, idx-1, res);
        helper(root->right, idx+1, res);
    }
};
