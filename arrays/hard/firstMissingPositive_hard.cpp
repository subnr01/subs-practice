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
        
        /* Basically we try to sort here, 
        only if the number is -1 or more than n, then
        we leave it in its position,
        as it becomes convinient for us when we compare.
        Other numbers when we sort, we make sure the swap
        happens with the next postive number and in turn
        helps to find the first positive integer.
        
        The important thing is
        
        m = nums[i] - 1;
        */
        
        for (i=0; i<n; i++) 
        {
              
            while (nums[i] > 0 && nums[i] <= n)
            {
                if( nums[nums[i]-1] != nums[i] ) {
                    swap(nums[i],nums[nums[i]-1]);
                }
                else {
                    break;
                }
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
