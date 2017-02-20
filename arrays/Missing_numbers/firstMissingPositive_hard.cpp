/*
Given an unsorted integer array, find the first missing positive integer.

For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/

class Solution {
public:
    int firstMissingPositive(vector<int>&nums) {
       
        int i;
        int target;
        int n = nums.size();
        for (i=0; i<n; i++) 
        {
           
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i]) 
            {
                swap(nums[i],nums[nums[i]-1]);
            }
        }
        /*
        At this stage
        nums[] = {1, -1, 3, 4}
        */
        for (i=0; i<n; i++)
        {
            if (nums[i] != i+1)
            {
                return i+1;
            }
        }
        
        return n+1; 
      
    }
};
