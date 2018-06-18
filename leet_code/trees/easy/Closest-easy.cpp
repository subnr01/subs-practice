
/*
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.


*/

class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        
        while (root)
        {
            if (root->val == target)
            {
                return root->val;
            }
            
            if (abs(target - root->val) < abs(target - closest))
            {
                closest = root->val;
            }
            
            root = (target > root->val) ? root->right: root->left;
        }
        
        return closest;
        
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

