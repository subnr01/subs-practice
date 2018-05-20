/*

Maximum Size Subarray Sum Equals k

Given an array nums and a target value k, find the maximum length of a subarray that sums to k. 
If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:
Given nums = [1, -1, 5, -2, 3], k = 3,
return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Example 2:
Given nums = [-2, -1, 2, 1], k = 1,
return 2. (because the subarray [-1, 2] sums to 1 and is the longest)

Follow Up:
Can you do it in O(n) time?

*/

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int n = nums.size();
        
        unordered_map<int, int> map;
        int sum = 0;
        int maxlen = 0;
        
        for (int i = 0; i < n; i++)
        {
            //cumulative sum
            sum += nums[i];
            int diff = sum - k;
            
            if (diff == 0) {
                maxlen = i + 1;
            } 
            // See how the logic is here.
            // the distance from the diff
            // to the current index.
            // examlple (1, 2, 3, 4, 5 and k = 12)
            // answer is 3.
            else if (map.find(diff) != map.end())
            {
                maxlen = max(maxlen, i - map[diff]);
            }
            
            if (map.find(sum) == map.end())
            {
                map[sum] = i;
            }
            
        }
        return maxlen;
        
    }
};
