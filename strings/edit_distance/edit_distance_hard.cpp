/*

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2.
(each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character

*/

/* 
This is a dynamic programming question.
*/


/*
Solution with the 2D version: relatively simpler
*/

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        if(m==0 || n==0 )return max(m,n);
        int dp[m+1][n+1];
        for(int i=0; i<=m; i++)  dp[i][0] = i;
        for(int i=0; i<=n; i++)  dp[0][i] = i;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(word1[i] == word2[j]) dp[i+1][j+1] = dp[i][j];
                else dp[i+1][j+1] = min( min(dp[i+1][j]+1, dp[i][j+1]+1), dp[i][j]+1);
            }
        }
        return dp[m][n];
    }
};


/*
Solution with the 
1D version
*/

https://discuss.leetcode.com/topic/17639/20ms-detailed-explained-c-solutions-o-n-space/2




