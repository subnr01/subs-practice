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
        
        size_t m = word1.size();
        size_t n = word2.size();
        
        vector<vector<int>> dp (m+1, vector<int>(n+1, 0));
        
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if(i == 0 || j == 0) {
                    dp[i][j] = 0;
                }
                else {
                    if (word1[i - 1] == word2[j - 1]) {
                        dp[i][j] = dp[i-1][j-1] + 1;
                    } else {
                        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                    }
                }
            }
        }
        
        int val = dp[m][n];
        return (m + n) - 2 * val;        
    }
};
