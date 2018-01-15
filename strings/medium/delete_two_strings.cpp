/*
 Delete Operation for Two Strings
 Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, 
 where in each step you can delete one character in either string.

Example 1:
Input: "sea", "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".

*/


//Soln
//Basically it comes down to the DP formula
/**
 * dp[i][j] = a[i] == b[j] ? dp[i + 1][j + 1] :
 *            min(1 + dp[i + 1][j],  // delete a[i] + mindist between a.substr(i+1), b.substr(j)
 *                1 + dp[i][j + 1])  // delete b[j] + mindist between a.substr(i), b.substr(j+1)
 */
//Check out the 1D version later.

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = m; i >= 0; i--) {
            for (int j = n; j >= 0; j--) {
                if (i < m || j < n) {
                    dp[i][j] = (i < m && j < n && word1[i] == word2[j]) ?
                               dp[i+1][j+1]:
                               1 + min(i < m ? dp[i+1][j]: INT_MAX, j < n? dp[i][j+1]: INT_MAX);  
                }
            }
        }
        return dp[0][0];
        
    }
};
