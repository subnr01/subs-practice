/*
Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1

Your algorithm should run in O(n) time and uses constant space.
*/

/*

what we are trying to do is to see
--> whether the array values are within boundaries
--> whether a[0] == 1, a[1] == 2, a[2] == 3 and so on...
--> if it is not case with the above two conditions, then we swap a[i] and a[a[i] - 1]
--> when we find the first element where a[i] != i+1, then we return i+1;
--> but if we find everything is inorder, then we return a.size() + 1;
*/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.size()==0)
            return 1;
        int i=0;
        while(i<nums.size()){            
            if(nums[i]<=0 || 
               nums[i]>nums.size() || 
               nums[i]==nums[nums[i]-1]){
               //SEE how i is incremented only in this case
                i++;
            }else if(nums[i]!=i+1){
                swap(nums[i],nums[nums[i]-1]);  
            } 
        }
        for(i=0;i<nums.size();i++){
            if(nums[i]!=i+1){
                // we have to return i+1
                return i+1;
            }
        }
        return nums.size()+1;
    }
};



//Related topics: array
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


