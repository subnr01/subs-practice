/*

Contiguous Array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

Example 1:
Input: [0,1]
Output: 2
Explanation: [0, 1] is the longest contiguous subarray with equal number of 0 and 1.
Example 2:
Input: [0,1,0]
Output: 2
Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

*/


class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> map;
        int n = nums.size();
        int zero = 0;
        int one = 0;
        int maxlen = 0;;
        map[0] = -1;
        
        for (int i = 0; i < n; i++)
        {
            if (nums[i]) {
                one++;
            } else {
                zero++;
            }
            
            auto it = map.find(one - zero);
            if (it != map.end())
            {
                maxlen = max(maxlen, i - it->second);
            } else {
                map[one - zero] = i;
            }
        }
        
        return maxlen;
        
    }
};


