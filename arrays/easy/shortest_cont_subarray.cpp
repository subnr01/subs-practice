/*

Given an integer array, you need to find one continuous subarray that if you only sort this subarray in
ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted
in ascending order.

*/

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums)
    {
        int left = 0;
        int right = 0;
        size_t sz = nums.size();
        if (sz <= 1) {
            return 0;
        }
        
        while(left < sz - 1 && nums[left] <= nums[left+1]) {
            left++;
        }
        
        if(left == sz - 1) {
            return 0;
        }
        right = sz - 1;
        while(right > 1 && nums[right] >= nums[right - 1]) {
            right --;
        }
        
        int rmin = INT_MAX;
        int lmax = INT_MIN;
        for ( int i = left; i <= right; i++){
            if(nums[i] > lmax) {
                lmax = nums[i];
            }
            if(nums[i] < rmin) {
                rmin = nums[i];
            }
        }
        
        while(left >= 0 && nums[left] > rmin) --left;
        
        while(right < sz && nums[right] < lmax) ++right;
        
        return (right - left - 1);
        
    }
};
