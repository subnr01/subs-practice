/*
Given two integers n and k, find how many different arrays consist of numbers from 1 to n 
such that there are exactly k inverse pairs.

We define an inverse pair as following: For ith and jth element in the array, if i < j 
and a[i] > a[j] then it's an inverse pair; Otherwise, it's not.

Since the answer may be very large, the answer should be modulo 109 + 7.

Example 1:
Input: n = 3, k = 0
Output: 1
Explanation: 
Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pair.
Example 2:
Input: n = 3, k = 1
Output: 2
Explanation: 
The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
Note:
The integer n is in the range [1, 1000] and k is in the range [0, 1000].

*/


//https://leetcode.com/problems/k-inverse-pairs-array/solution/

//https://discuss.leetcode.com/topic/93815/java-dp-o-nk-solution/2

//there seeems to be faster solns, but this one is shorter than the rest. (70 %)
 class Solution {
public:
    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n+1, vector<int>(k+1));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i){
            dp[i][0] = 1;
            for(int j = 1; j <= k; ++j){
                dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % mod;
                if(j - i >= 0){
                    dp[i][j] = (dp[i][j] - dp[i-1][j-i] + mod) % mod; 
                    //It must + mod, If you don't know why, you can check the case 1000, 1000
                }
            }
        }
        return dp[n][k];
    }
private:
    const int mod = pow(10, 9) + 7;
};
