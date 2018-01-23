/*
Given an array of n positive integers and a positive integer s, find the minimal length of 
a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

*/

//good soln
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        
        int sum = 0;
        int minlen = INT_MAX;
        
        int i = 0;
        
        for (int j = 0; j < n; j++)
        {
            sum += nums[j];
            while (sum >= s)
            {
                int len = j - i + 1;
                minlen = min(minlen, len);
                /// look how sum is decremented 
                // and i is moved forward until 
                // sum is less than s.
                sum -= nums[i];
                i++;
            }
        }
        
        // We need to check for INT_MAX 
        // because we may not find a soln for
        // cases such as {1,1} and 4.
        return minlen == INT_MAX? 0: minlen;
    }
};
