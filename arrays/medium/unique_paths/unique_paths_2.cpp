
/*
Follow up for "Unique Paths":
Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.
For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2
*/

//unoptimised version
class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int>>& grid) {
            int m = grid.size();
            int n = m == 0 ? 0 : grid[0].size();
            if( !m || !n || grid[m-1][n-1] == 1 ) {
                return 0;
            }
            
            vector<vector<int>> dp( m, vector<int>(n, 0));
            
            for( int i = 0; i < m; i++) 
            {
                if( grid[i][0] != 1 ) {
                    dp[i][0] = 1;
                }
                else {
                    break;
                }
            }
    
            for (int i = 0; i < n; i++ ) 
            {
                if( grid[0][i] != 1 ) { 
                    dp[0][i] = 1; 
                }
                else { 
                    break;
                }
            }
            
            for( int i = 1; i < m; i++ ) { 
                for( int j = 1; j < n; j++ ) {
                    int a = grid[i-1][j] == 1? 0: dp[i-1][j];
                    int b = grid[i][j-1] == 1? 0: dp[i][j-1];
                    dp[i][j] = a + b;
                }
            }
            
            return dp[m-1][n-1];
        }
};

//optimised version
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<int> dp(n);
        dp[0] = 1;
       
        
        for(int i = 0 ; i < m ; ++i)
        {
            for(int j = 0 ; j < n ; ++j)
            {
                if(obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                }
                else if (j >0) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        return dp[n-1];
    }
};
