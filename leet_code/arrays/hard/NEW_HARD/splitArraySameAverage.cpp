/*

In a given integer array A, we must move every element of A to either list B or list C. (B and C initially start empty.)

Return true if and only if after such a move, it is possible that the average value of B is equal to the
average value of C, and B and C are both non-empty.

Example :
Input: 
[1,2,3,4,5,6,7,8]
Output: true
Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.

*/


//inefficient, need to find a efficient one
class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int n = A.size(), m = n/2, totalSum = accumulate(A.begin(), A.end(), 0);
        sort(A.rbegin(), A.rend()); // Optimization
        for (int i = 1; i <= m; ++i) 
            if (totalSum*i%n == 0 && combinationSum(A, 0, i, totalSum*i/n)) return true;
        return false;
    }
    bool combinationSum(vector<int>& nums, int idx, int k, int tar) {
        if (tar > k * nums[idx]) return false; // Optimization, A is sorted from large to small
        if (k == 0) return tar == 0;
        for (int i = idx; i <= nums.size()-k; ++i) 
            if (nums[i] <= tar && combinationSum(nums, i+1, k-1, tar-nums[i])) return true;
        return false;
    }
};

