/*

Sorted array to BST

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
 
 
*/


class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.size() == 0)
            return NULL;
        return arraytoBST(nums, 0 , nums.size()-1);
    }
    
    TreeNode *arraytoBST(vector<int>  &nums, int start, int end)
    {
        if (start > end) {
            return NULL;
        }
        int mid = (start + end)/2;
        
        TreeNode *root = new TreeNode(nums[mid]);
        
        //start to (mid-1) is the left side of the tree.
        root->left = arraytoBST(nums, start, mid-1);
          
        //(mid + 1) to end is the right side of the tree.
        root->right = arraytoBST(nums, mid+1, end);
        
        return root;
    }
};
