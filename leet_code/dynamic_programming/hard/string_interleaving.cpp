/*

String Intervleaving

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

*/


//Check out BFS and DFS solutions if possible.

class Solution { 
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length(), l = s3.length();
        if (m > n) return isInterleave(s2, s1, s3);
        if (l != m + n) return false;
        bool *dp = new bool[m + 1]();
        dp[0] = true;
        for (int i = 1; i <= m; i++)
            dp[i] = dp[i - 1] && s3[i - 1] == s1[i - 1];
        for (int j = 1; j <= n; j++) {
            dp[0] = dp[0] && s3[j - 1] == s2[j - 1];
            for (int i = 1; i <= m; i++)
                dp[i] = (dp[i - 1] && s3[i + j - 1] == s1[i - 1]) || (dp[i] && s3[i + j - 1] == s2[j - 1]);
        }
        return dp[m];
    }
};

