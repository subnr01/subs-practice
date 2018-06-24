/*

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
   
*/
   


/*

DP Solution
*/

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> res;
        if (!n) {
            return res;
        }
        
        int begin = 1;
        int end = n;
        return gen(begin, end);
        
    }
    
    vector<TreeNode*> gen(int begin, int end) 
    {
        vector<TreeNode*> ret;
        if (begin > end)
        {
            ret.push_back(nullptr);
            return ret;
        }
        
        if (begin == end)
        {
            TreeNode* root = new TreeNode(begin);
            ret.push_back(root);
            return ret;
        }
        
        for (int mid = begin; mid <= end; mid++)
        {
            vector<TreeNode*> leftNodes = gen(begin, mid - 1);
            vector<TreeNode*> rightNodes = gen(mid + 1, end);
            
            for (auto ln : leftNodes) 
            {
                for (auto rn : rightNodes)
                {
                    TreeNode *root = new TreeNode(mid);
                    root->left = ln;
                    root->right = rn;
                    ret.push_back(root);
                    
                }
            }
        }
        
        return ret;
        
    }
        
    
};

Debugging:

pushing: 3
2
right: 3
done
pushing: 2
3
left: 2
done
1
right: 2
1
right: 3
done
pushing: 1
pushing: 3
2
left: 1
right: 3
done
pushing: 2
1
right: 2
done
pushing: 1
2
left: 1
done
3
left: 1
done
3
left: 2
done
   
