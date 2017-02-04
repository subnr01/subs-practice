/*
Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
For example:
Given BST [1,null,2,2],
   1
    \
     2
    /
   2
return [2].

Note: If a tree has more than one mode, you can return them in any order.

Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).

*/


class Solution {
public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int,int> counts;
        int max = 0;
        utill(root, counts, max);
        
        vector<int> modes;
        for(auto& y : counts){
            if(y.second == max) modes.push_back(y.first);
        }
        return modes;
    }
    
    void utill(TreeNode* r, unordered_map<int,int> &counts, int &max){
        if(r == nullptr) return;
        
        ++counts[r->val];
        max = std::max(max, counts[r->val]);
        utill(r->left, counts, max);
        utill(r->right, counts, max);
    }
    
};
