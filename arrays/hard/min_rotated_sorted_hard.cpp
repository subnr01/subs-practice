/*
Follow up for "Find Minimum in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.



*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        
    int low = 0;
    int high = nums.size()-1;
    
    //This is the key, we are doing this 
    //because we want to avoid duplicates
    //on both halves of the array.
    while (low < high && nums[low] == nums[high]) {
            high -= 1;  // or left += 1; if index is not asked
    }
    
    //normal workings of how to return 
    // pivot element in an sorted rotated array
    while (low < high)
    {
        if (nums[low] < nums[high]) {
            return nums[low];
        }
        
        int mid = (low + high)/2;
        
        if (nums[low] > nums[mid])
        {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    return nums[low];    
    }
};
