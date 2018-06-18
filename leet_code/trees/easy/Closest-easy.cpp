
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
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        findClosest(root, target, closest);
        return closest;
    }
    
    void findClosest(TreeNode *root, double target, int &closest)
    {
        if (!root) {
            return;
        }
        
        if (target == root->val) {
            closest = root->val;
            return;
        }
        
        
        if (abs (target - root->val) < abs(target - closest))
        {
            closest = root->val;
        }
        
        if (target > root->val)
        {
            findClosest(root->right, target, closest);
        } else {
            findClosest(root->left, target, closest);
        }
    }
};class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        findClosest(root, target, closest);
        return closest;
    }
    
    void findClosest(TreeNode *root, double target, int &closest)
    {
        if (!root) {
            return;
        }
        
        /*
        Target is compared against root->val
        and then closest is updated
        */
        if (target == root->val) {
            closest = root->val;
            return;
        }
        
        
        if (abs (target - root->val) < abs(target - closest))
        {
            closest = root->val;
        }
        
        if (target > root->val)
        {
            findClosest(root->right, target, closest);
        } else {
            findClosest(root->left, target, closest);
        }
    }
};

