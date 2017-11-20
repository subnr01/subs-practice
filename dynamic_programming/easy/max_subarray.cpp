/*

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        
        int sz = nums.size();
        
        vector<int> sum;
        int maxi = nums[0];
        sum.push_back(nums[0]);
        
        for (int i = 1; i < sz; i++) {
            int temp = max(nums[i],sum[i-1] + nums[i]);
            sum.push_back(temp);
            maxi = max(maxi, sum[i]);
        }
        
        return maxi;
    }
};
