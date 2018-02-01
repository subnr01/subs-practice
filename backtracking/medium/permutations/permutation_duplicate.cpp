/*
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

*/



class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int start = 0;
        genPerm(res, nums, start);
        return res;
    
    }
    
    void genPerm(vector<vector<int>> &res, vector<int> nums, int start)
    {
        
        if(start == nums.size()) {
            res.push_back(nums);
            return;
        }
  
        for (int i = start; i < nums.size(); i++) {
            if ( i == start || nums[i] != nums[start]) {
                swap(nums[i], nums[start]);
                genPerm(res, nums, start+1);
                /* See we are not swapping back */
                //swap(nums[i], nums[start]);
                
            }      
        }
        
    }
    
};



//Solution using map
https://discuss.leetcode.com/topic/18471/my-c-recursive-dfs-backtracking-solutions
