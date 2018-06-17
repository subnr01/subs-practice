/*

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. 
Hence return [3, 14.5, 11].
*/



//it has both BFS and DFS solution


//BFS solution
//Time complexity: O(n) and space complexity is O(m) where m is the max number of nodes at any level
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            long temp=0;
            int s=q.size();
            for(int i=0;i<s;i++) {
		//queue is popped in the inner loop
                TreeNode* t=q.front();
                q.pop();
                if(t->left) q.push(t->left);
                if(t->right) q.push(t->right);
                temp+=t->val;
            }
            res.push_back((double)temp/s);
        }
        return res;
    }
};

//DFS Solution

// Time compexity is O(N)
// Spce complexity is . O(h) : hieght of the tree
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        //important that sum is double or long for cases of overflow
	//example input : [2147483647,2147483647,2147483647]
        std::vector<double> sum;
        std::vector<int> counts;

        helper(root, sum, counts, 0);

        std::vector<double> result;

        for (int i = 0; i < sum.size(); ++i) {
            result.push_back(sum[i] / counts[i]);
        }

        return result;

    }

    void helper(TreeNode* root, std::vector<double>& sum, std::vector<int>& counts, int level) {

        if (root == nullptr) {
            return;
        }

        if (level == sum.size() && level == counts.size()) {
            sum.push_back(root->val);
            counts.push_back(1);
        } else {
            sum[level] += root->val;
            counts[level] += 1;
        }
				
        helper(root->left, sum, counts, level + 1);
        helper(root->right, sum, counts, level + 1);
    }
};


