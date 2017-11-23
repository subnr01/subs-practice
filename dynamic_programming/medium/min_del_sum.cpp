/*

Given two strings s1, s2, find the lowest ASCII sum of deleted characters to make two strings equal.

Example 1:
Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:
Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d]+101[e]+101[e] to the sum.  Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
Note:

0 < s1.length, s2.length <= 1000.
All elements of each string will have an ASCII value in [97, 122].


*/

https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/solution/


//C++ DP
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int j = 1; j <= n; j++)
            dp[0][j] = dp[0][j-1]+s2[j-1];
        for (int i = 1; i <= m; i++) {
            dp[i][0] = dp[i-1][0]+s1[i-1];
            for (int j = 1; j <= n; j++) {
                if (s1[i-1] == s2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else 
                    dp[i][j] = min(dp[i-1][j]+s1[i-1], dp[i][j-1]+s2[j-1]);
            }
        }
        return dp[m][n];
    }
};


//Optimised
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        vector<int> dp(n+1, 0);
        for (int j = 1; j <= n; j++)
            dp[j] = dp[j-1]+s2[j-1];
        for (int i = 1; i <= m; i++) {
            int t1 = dp[0];
            dp[0] += s1[i-1];
            for (int j = 1; j <= n; j++) {
                int t2 = dp[j];
                dp[j] = s1[i-1] == s2[j-1]? t1:min(dp[j]+s1[i-1], dp[j-1]+s2[j-1]);
                t1 = t2;
            }
        }
        return dp[n];
    }
};

class Solution {
    public int minimumDeleteSum(String s1, String s2) {
        int[][] dp = new int[s1.length() + 1][s2.length() + 1];

        for (int i = s1.length() - 1; i >= 0; i--) {
            dp[i][s2.length()] = dp[i+1][s2.length()] + s1.codePointAt(i);
        }
        for (int j = s2.length() - 1; j >= 0; j--) {
            dp[s1.length()][j] = dp[s1.length()][j+1] + s2.codePointAt(j);
        }
        for (int i = s1.length() - 1; i >= 0; i--) {
            for (int j = s2.length() - 1; j >= 0; j--) {
                if (s1.charAt(i) == s2.charAt(j)) {
                    dp[i][j] = dp[i+1][j+1];
                } else {
                    dp[i][j] = Math.min(dp[i+1][j] + s1.codePointAt(i),
                                        dp[i][j+1] + s2.codePointAt(j));
                }
            }
        }
        return dp[0][0];
    }
}
