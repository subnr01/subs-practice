/*
Given a string S, find the number of different non-empty palindromic subsequences in S,
and return that number modulo 10^9 + 7.

A subsequence of a string S is obtained by deleting 0 or more characters from S.

A sequence is palindromic if it is equal to the sequence reversed.

Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some i for which A_i != B_i.

Example 1:
Input: 
S = 'bccb'
Output: 6
Explanation: 
The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc', 'bcb', 'bccb'.
Note that 'bcb' is counted only once, even though it occurs twice.
Example 2:
Input: 
S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
Output: 104860361
Explanation: 
There are 3104860382 different non-empty palindromic subsequences, which is 104860361 modulo 10^9 + 7.

*/


//Related topics: dynamic programming, string


class Solution {
    /* basically the hard part of this dynamic programming problem is to 
       eliminate the duplicates. let dp[i][j] represents the number of 
       palindromic sequences in (i, j) then:
       if S[i] != S[j]
            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]

       elsif S[i] == S[j]. Because we can generate sequences by attach two chars on two 
       ends like this: S[i] + any subsequences in (i + 1, j - 1) + S[j]
        dp[i][j] = 2 * dp[i + 1][j - 1] - duplicates
       However, counting duplicates can be tricky. We can scan from two ends to find 
       a inner pair with same character. Then the number of the duplicates is actually
       the number of subsequences in this pair.
      */
public:
    int countPalindromicSubsequences(string S) {
        int BIG = 1000000007;
        int len = S.size();
        if(!len) return 0;
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for(int i = 0; i < len; ++i)
            dp[i][i] = 1;
        for(int i = len - 1; i >= 0; --i)
            for(int j = i + 1; j < len; ++j) 
                if(S[i] != S[j]) {
                    dp[i][j] = (dp[i + 1][j] + dp[i][j - 1]) % BIG;
                    dp[i][j] = (BIG - dp[i + 1][j - 1] + dp[i][j]) % BIG;
                } else {
                    dp[i][j] = (2 * dp[i + 1][j - 1]) % BIG;
                    int l = i + 1, r = j - 1;
                    while(l <= r && S[l] != S[i]) ++l;
                    while(l <= r && S[r] != S[j]) --r;
                    if(r < l) 
                        dp[i][j] = (dp[i][j] + 2) % BIG;
                    else if(r == l) 
                        dp[i][j] = (dp[i][j] + 1) % BIG;
                    else 
                        dp[i][j] = (BIG - dp[l + 1][r - 1] + dp[i][j]) % BIG;
                }
        return dp[0][len - 1];
    }
};
