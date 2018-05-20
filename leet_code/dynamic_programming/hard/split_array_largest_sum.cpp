/*

Given an array which consists of non-negative integers and an integer m, you can split the
array into m non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these m subarrays.

Note:
If n is the length of array, assume the following constraints are satisfied:

1 ≤ n ≤ 1000
1 ≤ m ≤ min(50, n)
Examples:

Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.

*/


//https://discuss.leetcode.com/topic/61395/c-fast-very-clear-explanation-clean-code-solution-with-greedy-algorithm-and-binary-search
//Binary search
class Solution {
private:
    bool doable (const vector<int>& nums, int cuts, long long max) {
        int acc = 0;
        for (num : nums) {
            // This step is unnecessary for this problem. I didn't discard this line because I want doable function more generalized.
            if (num > max) return false;
            else if (acc + num <= max) acc += num;
            else {
                --cuts;
                acc = num;
                if (cuts < 0) return false;
            }
        }
        return true;
    }
    
public:
    int splitArray(vector<int>& nums, int m) {
        long long left = 0, right = 0;
        for (num : nums) {
            left = max(left, (long long)num);
            right += num;
        }
        
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (doable(nums, m - 1, mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};




