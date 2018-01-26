/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.

*/


class Solution {

	public:
		bool search(vector<int>& nums, int target) {
			
			int size = nums.size();
			
			for(int i =0 ; i <size; i++){
                
				int n  = nums[i];
                
				if (n == target) {
                    
                    return true;
				}
				
			}
        return false;

        }
};
