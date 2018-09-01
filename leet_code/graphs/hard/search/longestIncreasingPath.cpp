/*
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

Input: nums = 
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
] 
Output: 4 
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:

Input: nums = 
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
] 
Output: 4 
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

*/


class Solution {
private:
    vector<vector<int>> cache;
    vector<pair<int, int>> direction;
    int m, n;
    int DFS(int i, int j, vector<vector<int>>& matrix) {
        if(cache[i][j] != 0) return cache[i][j];
        int longest = 1;
        for(auto dir : direction) {
            int x = i + dir.first, y = j + dir.second;
            if(x < 0 || x >= m || y < 0 || y >= n || matrix[x][y] <= matrix[i][j]) {
                continue;
            } else {
                longest = max(longest, DFS(x, y, matrix) + 1);
            }
        }
        cache[i][j] = longest;
        return longest;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        m = matrix.size(), n = matrix[0].size();
        direction.push_back(pair<int, int>(0, 1));
        direction.push_back(pair<int, int>(0, -1));
        direction.push_back(pair<int, int>(1, 0));
        direction.push_back(pair<int, int>(-1, 0));
        cache = vector<vector<int>>(m, vector<int>(n, 0));
        int longest = 1;
        for (int i = 0; i < m; i++) {
           for(int j = 0; j < n; j++) {
               longest = max(longest, DFS(i, j, matrix));
           } 
        }
        return longest;
    }
};


//another soln
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int res = 0;
        if(matrix.size()==0||matrix[0].size()==0)
            return res;
        int row = matrix.size(), column = matrix[0].size();
        //如何初始化vector的二维数组
        vector<vector<int>> dp(row, vector<int>(column, -1));
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                int localMax = dfs(matrix,dp,i,j);
                res = res>localMax?res:localMax;
            }
        }
        return res;
    }

private:
    int dfs(vector<vector<int>>& matrix,vector<vector<int>>& dp,int row,int column)
    {
        int cur = matrix[row][column];
        //访问当前节点
        int down=1,up=1,left=1,right=1;
        //分别向上下左右四个方向遍历
        if((row+1)<matrix.size()&&matrix[row+1][column]>cur)
        {
            if(dp[row+1][column]!=-1)
                down += dp[row+1][column];
            else
                down += dfs(matrix,dp,row+1,column);
        }
        if((row-1)>=0&&matrix[row-1][column]>cur)
        {
            if(dp[row-1][column]!=-1)
                up += dp[row-1][column];
            else
                up += dfs(matrix,dp,row-1,column);
        }
        if((column+1)<matrix[0].size()&&matrix[row][column+1]>cur)
        {
            if(dp[row][column+1]!=-1)
                right += dp[row][column+1];
            else
                right += dfs(matrix,dp,row,column+1);
        }
        if((column-1)>=0&&matrix[row][column-1]>cur)
        {
            if(dp[row][column-1]!=-1)
                left += dp[row][column-1];
            else
                left += dfs(matrix,dp,row,column-1);
        }
        dp[row][column] = max(max(down,up),max(right,left));
        return dp[row][column];
    }
};
