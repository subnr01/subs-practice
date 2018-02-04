/*

Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].



*/

class Solution {
public:
 vector<int> searchRange(vector<int>& nums, int target) {
    if (nums.size() == 0) {
        return vector<int> {-1,-1};
    } 
    int start = 0, end = nums.size(), mid, left, right;
    
    //See start is not equal to end here
    while (start < end) {
        mid = (start + end) / 2;
        //not the equality coomparision here
        if (nums[mid] >= target)
            end = mid;
        else
            start = mid + 1;
    }
    left = start;
    end = nums.size();
    //See start is not equal to end here
    while (start < end) {
        mid = (start + end) / 2;
        if (nums[mid] > target)
            end = mid;
        else
            start = mid + 1;
    }
    right = start;
    //we return (right - 1) on success....
    return left == right ? vector<int> {-1,-1} : vector<int> {left,right-1};
}
};
