/*
Example 1:

Input: root = [4,2,6,1,3,5,7], V = 2
Output: [[2,1],[4,3,6,null,null,5,7]]
Explanation:
Note that root, output[0], and output[1] are TreeNode objects, not arrays.

The given tree [4,2,6,1,3,5,7] is represented by the following diagram:

          4
        /   \
      2      6
     / \    / \
    1   3  5   7

while the diagrams for the outputs are:

          4
        /   \
      3      6      and    2
            / \           /
           5   7         1

*/

/*
This is quite an interesting problem, that can be asked in interviews.
What we do here is we return an array of TreeNodes "res".

Consider that there are three nodes in the tree and root->val >  V.

So the recursive call auto res1 = splitBST(root->left, V) will
give us res1 {root->left, NULL}.
Now to really split the tree, we set the root->val to NULL and then
set the final values for "res" which we will return as the solution.

These are the two statements that do that:
root->left = res1[1];
res[0]=res1[0];

and remember we assigned
root = res1[1];

so we split the tree into two:
res {root->left, root} which are the roots of the two subtrees.

*/

class Solution {
public:
  vector<TreeNode*> splitBST(TreeNode* root, int V) {
        vector<TreeNode *> res(2, NULL);
        if(root == NULL) return res;
        
        if(root->val > V){
            res[1] = root;
            auto res1 = splitBST(root->left, V);
            
            res[0]=res1[0];
        }else{
            res[0] = root;
            auto res1 = splitBST(root->right, V);
            root->right = res1[0];
            res[1] = res1[1];
        }
        
        return res;
    }
};
