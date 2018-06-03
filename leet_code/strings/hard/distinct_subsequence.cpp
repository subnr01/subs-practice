/*
Given a string S and a string T, count the number of distinct subsequences of S which equals T.

A subsequence of a string is a new string which is formed from the original string by deleting some 
(can be none) of the characters without disturbing the relative positions of the remaining characters.
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Example 1:

Input: S = "rabbbit", T = "rabbit"
Output: 3
Explanation:

As shown below, there are 3 ways you can generate "rabbit" from S.
(The caret symbol ^ means the chosen letters)

rabbbit
^^^^ ^^
rabbbit
^^ ^^^^
rabbbit
^^^ ^^^
Example 2:

Input: S = "babgbag", T = "bag"
Output: 5
Explanation:

As shown below, there are 5 ways you can generate "bag" from S.
(The caret symbol ^ means the chosen letters)

babgbag
^^ ^
babgbag
^^    ^
babgbag
^    ^^
babgbag
  ^  ^^
babgbag
    ^^^
*/


//Related topics: dynamic progrmming


/*
Well, a dynamic programming problem. Let's first define its state dp[i][j] to be the number of 
distinct subsequences of t[0..i - 1] in s[0..j - 1]. Then we have the following state equations:

General case 1: dp[i][j] = dp[i][j - 1] if t[i - 1] != s[j - 1];
General case 2: dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1] if t[i - 1] == s[j - 1];
Boundary case 1: dp[0][j] = 1 for all j;
Boundary case 2: dp[i][0] = 0 for all positive i.
Now let's give brief explanations to the four equations above.

If t[i - 1] != s[j - 1], the distinct subsequences will not include s[j - 1] and thus all the number 
of distinct subsequences will simply be those in s[0..j - 2], which corresponds to dp[i][j - 1];
If t[i - 1] == s[j - 1], the number of distinct subsequences include two parts: those with s[j - 1] 
and those without;
An empty string will have exactly one subsequence in any string :-)
Non-empty string will have no subsequences in an empty string.
Putting these together, we will have the following simple codes (just like translation :-)):

*/

/*
dp[i][j] to be the number of distinct subsequences of t[0..i - 1] in s[0..j - 1].

dp[i][j] means the number of distinct subsequences of t.substr(0, i) in s.substr(0,j).
if i = 0, t.substr(0,0) = "", we can say there are 1 instance of that for "". So, 
initialize dp[0][j] = 1, and other dp[i][j] = 0.

*/

//Refer this
//https://leetcode.com/problems/distinct-subsequences/discuss/37387/A-DP-solution-with-clarification-and-explanation
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.length();
        int n = s.length();
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0));
        
        for (int j = 0; j <= n; j++) 
        {
            dp[0][j] = 1;
        }
        
        for (int j = 1; j <= n; j++) 
        {
            for (int i = 1; i <= m; i++) 
            {
                if (t[i - 1] == s[j - 1]) {
                    dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }

            }
        }
        return dp[m][n];
    }
};  

//1-D array
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.length(), n = s.length();
        vector<int> cur(m + 1, 0);
        cur[0] = 1;
        for (int j = 1; j <= n; j++) { 
            int pre = 1;
            for (int i = 1; i <= m; i++) {
                int temp = cur[i];
                cur[i] = cur[i] + (t[i - 1] == s[j - 1] ? pre : 0);
                pre = temp;
            }
        }
        return cur[m];
    }
};

