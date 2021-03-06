/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom 
right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:
[[1,3,1],
 [1,5,1],
 [4,2,1]]
Given the above grid map, return 7. Because the path 1→3→1→1→1 minimizes the sum.

*/

Related topics: array, DP


//dp 6 ms
/*
This is a typical DP problem. Suppose the minimum path sum of arriving at 
point (i, j) is S[i][j], then the state equation is S[i][j] = min(S[i - 1][j], S[i][j - 1]) + grid[i][j].
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size(); 
        if(m==0) return 0; 
        int n=grid[0].size(); 
        
        vector<vector<int>> dp(m, vector<int>(n, 0));
        
        dp[0][0]=grid[0][0]; 
        
        for(int i=1; i<m; i++) dp[i][0]=dp[i-1][0]+grid[i][0]; 
        
        for(int j=1; j<n; j++) dp[0][j]=dp[0][j-1]+grid[0][j]; 
        
        for(int i=1; i<m; i++)
            for(int j=1; j<n; j++){
                dp[i][j]=min(dp[i-1][j], dp[i][j-1])+grid[i][j]; 

            }
        
        return dp[m-1][n-1]; 

    }
};


//dp 1d array (9ms)
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> cur(m, grid[0][0]);
        for (int i = 1; i < m; i++)
            cur[i] = cur[i - 1] + grid[i][0]; 
        for (int j = 1; j < n; j++) {
            cur[0] += grid[0][j]; 
            for (int i = 1; i < m; i++)
                cur[i] = min(cur[i - 1], cur[i]) + grid[i][j];
        }
        return cur[m - 1];
    }
};

