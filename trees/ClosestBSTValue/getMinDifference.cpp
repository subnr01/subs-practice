https://leetcode.com/problems/minimum-absolute-difference-in-bst/?tab=Description

/*

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).


*/


class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        long mindiff = INT_MAX;
        TreeNode* prev = nullptr;
        find(root, prev, mindiff);
        return mindiff;
    }
private:
    void find(TreeNode* node, TreeNode*& prev, long& mindiff) {
        if (node->left) { 
            find(node->left, prev, mindiff);
        }

        if (prev != nullptr) {
            mindiff = std::min(mindiff, (long)abs(node->val - prev->val));
        }
        prev = node;

        if (node->right) {
            find(node->right, prev, mindiff);
        }
    }
};

What if it is not a BST? (Follow up of the problem) The idea is to put values in a TreeSet and 
then every time we can use O(lgN) time to lookup for the nearest values.

Solution 2 - Pre-Order traverse, time complexity O(NlgN), space complexity O(N).

// C++ implementation
void getMinimumDifference(TreeNode* root, set<int, int> &myset, int &min) {

        if (!root) {
        	return;
        }
        
        if (!myset.empty()) {
        	std::set<int>::iterator itup;
        	int upper = 0;
        	int lower = 0;

        	// Find the upper bound
        	itup=myset.upper_bound (root->val); 
        	upper = *itup;

        	// Find the lower bound
        	--itup;
        	if( itup != myset.end())
        	{
        		lower = *itup;
        	}

        	// Find the minimum difference
            min = min(min, abs(root.val - lower));
            min = min(min, abs(root.val - upper));
            
        }
        
        // Add the new element into the set
        set.add(root->val);
        
        // Perform DFS
        getMinimumDifference(root->left, myset, min);
        getMinimumDifference(root->right, myset, min);
        
        return min;
    }
