/*
Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root. 
Boundary includes left boundary, leaves, and right boundary in order without duplicate nodes.

Left boundary is defined as the path from root to the left-most node. Right boundary is defined
as the path from root to the right-most node. If the root doesn't have left subtree or right subtree, 
then the root itself is left boundary or right boundary. Note this definition only applies to the
input binary tree, and not applies to any subtrees.

The left-most node is defined as a leaf node you could reach when you always firstly travel to 
the left subtree if exists. If not, travel to the right subtree. Repeat until you reach a leaf node.

The right-most node is also defined by the same way with left and right exchanged.

Example 1
Input:
  1
   \
    2
   / \
  3   4

Ouput:
[1, 3, 4, 2]

Explanation:
The root doesn't have left subtree, so the root itself is left boundary.
The leaves are node 3 and 4.
The right boundary are node 1,2,4. Note the anti-clockwise direction means you should output reversed right boundary.
So order them in anti-clockwise without duplicates and we have [1,3,4,2].
Example 2
Input:
    ____1_____
   /          \
  2            3
 / \          / 
4   5        6   
   / \      / \
  7   8    9  10  
       
Ouput:
[1,2,4,7,8,9,10,6,3]

Explanation:
The left boundary are node 1,2,4. (4 is the left-most node according to definition)
The leaves are node 4,7,8,9,10.
The right boundary are node 1,3,6,10. (10 is the right-most node).
So order them in anti-clockwise without duplicate nodes we have [1,2,4,7,8,9,10,6,3].

*/

//DFS Soln
class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int>res;
        if(!root) return res;
        res.push_back(root->val);
        vector<int>lefts,leaves,rights;
        
        getLeft(root->left,lefts);
        getLeaves(root->left,leaves);
        getLeaves(root->right,leaves);
        getRight(root->right,rights); 
        reverse(rights.begin(),rights.end());
        
        for(auto l:lefts) res.push_back(l);
        for(auto leave:leaves) res.push_back(leave);
        for(auto r:rights) res.push_back(r);
        
        return res;   
    }
private:
    void getLeft(TreeNode* curr,vector<int>&lefts)
    {
        if(!curr|| (curr->left==NULL && curr->right==NULL)) return;
        lefts.push_back(curr->val);
        if(curr->left!=NULL) 
            getLeft(curr->left,lefts);
        else
            getLeft(curr->right,lefts);
    }
    
    void getLeaves(TreeNode * curr,vector<int>&leaves)
    {
        if(!curr) return;
        if(curr->left==NULL && curr->right==NULL) leaves.push_back(curr->val);
        getLeaves(curr->left,leaves);
        getLeaves(curr->right,leaves);
    }
    
    void getRight(TreeNode*curr,vector<int>&rights)
    {
        if(!curr|| (curr->left==NULL && curr->right==NULL)) return;       
        rights.push_back(curr->val);
        if(curr->right) getRight(curr->right,rights);
        else getRight(curr->left,rights);
    }
};

//perorder postorder hybrid

class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> bounds;
        if (root) {
            bounds.push_back(root->val);
            getBounds(root->left, bounds, true, false);
            getBounds(root->right, bounds, false, true);
        }
        return bounds;
    }

private:
    void getBounds(TreeNode* node, vector<int>& res, bool lb, bool rb) {
        if (!node)  return;
        if (lb) res.push_back(node->val);
        if (!lb && !rb && !node->left && !node->right)  res.push_back(node->val);
        getBounds(node->left, res, lb, rb && !node->right);
        getBounds(node->right, res, lb && !node->left, rb);
        if (rb) res.push_back(node->val);
    }
};




