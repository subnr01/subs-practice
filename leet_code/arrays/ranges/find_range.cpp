/*

Given a sorted array of integers, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].


*/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        
        vector<int>ans{0,0};
        
        ans[0] = -1;
        ans[1] = -1;
        bs(nums, 0, nums.size() - 1,target, ans);
        return ans;
    }
    
    void bs(vector<int>& nums, int low, int high, int target, vector<int> &ans) {
        
        if (low >high) {
            return;
        }
        
        if (nums[low]==nums[high] && nums[low]==target) {
            ans[0] =  low;
            ans[1] =  high;
            return;
        }
        int mid = (high - low)/2 + low;
        if (nums[mid] < target) {
            bs(nums, mid+1, high,target, ans);
        }
        else if (nums[mid] > target) {
            bs(nums, low, mid-1,target, ans);
        }  else {
            
            int index = mid;
            
            while(index > low && nums[index] == nums[index-1]) {
                index --;
                
                
            }
            ans[0] = index;
            
            index = mid;
            
            while(index < high && nums[index] == nums[index+1]) {
                index++;
                
                
            }
            ans[1] = index;
        }
        return;
        
    }
};
