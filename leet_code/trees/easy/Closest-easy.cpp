
/*
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.


*/

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int result = root->val;
        
        while(root)
        {
            if ((double)root->val == target)
            {
                return root->val;
            }
            double a = abs(target - (double)result);
            double b = abs(target - (double)root->val);
            result = (a<b)?result:root->val;
            
            if (target > (double)root->val)
            {
                root = root->right;
            } else {
                root = root->left;
            }
        }
        return result;
        
    }
};


//RECURSIVE (BUT SLOWER)
class Solution {
public:
    void helper(TreeNode* root, double target, int& val)
    {
        if (root == nullptr) return;
        if (abs(root->val - target) < abs(val - target)) val = root->val;
        
        if (root->val > target) helper(root->left, target, val);
        else helper(root->right, target, val);
    }
    
    
    int closestValue(TreeNode* root, double target) {
        
        int val = root->val;
        helper(root, target, val);
        
        return val;
    }
};

