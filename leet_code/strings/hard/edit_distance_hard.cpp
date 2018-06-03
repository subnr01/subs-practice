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
1. Let dp[i][j] to be the minimum number of operations to convert word1[0..i - 1] to word2[0..j - 1].
2. Empty string case (either of them)
   dp[i][0] = i;
   dp[0][j] = j.
3. Suppose we have already known how to convert word1[0..i - 2] to word2[0..j - 2], which is dp[i - 1][j - 1]. 
   Now let's consider word[i - 1] and word2[j - 1]. If they are euqal, then no more operation is needed and 
   dp[i][j] = dp[i - 1][j - 1]. Well, what if they are not equal?
   
   If they are not equal, then we consider three cases:
   
   1. Replace word1[i - 1] by word2[j - 1] (dp[i][j] = dp[i - 1][j - 1] + 1 (for replacement));
   2. Delete word1[i - 1] and word1[0..i - 2] = word2[0..j - 1] (dp[i][j] = dp[i - 1][j] + 1 (for deletion));
   3. Insert word2[j - 1] to word1[0..i - 1] and 
   word1[0..i - 1] + word2[j - 1] = word2[0..j - 1] (dp[i][j] = dp[i][j - 1] + 1 (for insertion)).
   
   So we will consider the minimum of the above operations.
   
   The crux is 
   1. If we replace, then we need to move on and consider the remaining elements of A and B.
   2. If we delete something from A, then we need to consider the remaining elements of A and all
      the elements of B. (dp[i - 1][j])
   3. If we add something to A, then we need to consider all the elements of A (except the one added)
      with the remaining elements of B. (dp[i][j - 1])
 */

class Solution { 
public:
    int minDistance(string word1, string word2) { 
        int m = word1.length(); 
        int n = word2.length();
        
       /*
       dp[i][j] is the min operations to convert from
       word1[0..i - 1] to word2[0..j - 1]
       */
        vector<vector<int> > dp(m + 1, vector<int> (n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            dp[i][0] = i;
        }
        
        for (int j = 1; j <= n; j++) {
            dp[0][j] = j;  
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    /* if they are both same, then no need for any operation */
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    /* consider one less characters of A and B */
                    int replace = 1 + dp[i-1][j-1];
                    /* consider 1 less character of A and all of B */
                    int remove = 1 + dp[i-1][j];
                    /* consider all of A and one less of B */
                    int add = 1 + dp[i][j-1];
                    dp[i][j] = min(add, min(remove, replace));
                }
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

class Solution { 
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<int> cur(m + 1, 0);
        for (int i = 1; i <= m; i++)
            cur[i] = i;
        for (int j = 1; j <= n; j++) {
            int pre = cur[0];
            cur[0] = j;
            for (int i = 1; i <= m; i++) {
                int temp = cur[i];
                if (word1[i - 1] == word2[j - 1])
                    cur[i] = pre;
                else cur[i] = min(pre + 1, min(cur[i] + 1, cur[i - 1] + 1));
                pre = temp;
            }
        }
        return cur[m]; 
    }
}; 


