/*

Sorted array to BST
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
        
        
        root->left = arraytoBST(nums, start, mid-1);
        root->right = arraytoBST(nums, mid+1, end);
        
        return root;
    }
};
