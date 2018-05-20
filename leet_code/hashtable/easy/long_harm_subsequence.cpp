/*

 Longest Harmonious Subsequence
 ---------------------------------
 
 
We define a harmonious array is an array where the difference between its maximum value and its
minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence
among all its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
 
 */

//my soln
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> myMap;
        
        int n = nums.size();
        
        for (int i = 0; i < n; i++)
        {
            myMap[nums[i]]++;
        }
        
        int res = 0;
        
        for (auto m: myMap)
        {
            if (myMap.count(m.first - 1) > 0) {
                res = max(res, (myMap[m.first] + myMap[m.first - 1]));
            }
        }
        return res;
    }
};
