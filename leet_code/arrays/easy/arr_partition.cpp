/*
Given an array of 2n integers, your task is to group these integers into n pairs of integer, say
(a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).

*/


/*
In short, the sum of all number is fixed, to maximize the sum of smaller group, you want to minimize the diff of the sum of 2 groups.
And the best way to do that is to pair the numbers that are next to each other in sorted order.
*/

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {
        int sum = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i += 2) {
            sum += nums[i];
        }
        
        return sum;
    }
};
