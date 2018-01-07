/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner
of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?
*/

/*
Using DFS
-------------
*/

public int uniquePaths(int m, int n) {
    return dfs(0,0,m,n);
}
 
public int dfs(int i, int j, int m, int n){
    if(i==m-1 && j==n-1){
        return 1;
    }
 
    if(i<m-1 && j<n-1){
        return dfs(i+1,j,m,n) + dfs(i,j+1,m,n);
    }
 
    if(i<m-1){
        return dfs(i+1,j,m,n);
    }
 
    if(j<n-1){
        return dfs(i,j+1,m,n);
    }
 
    return 0;
}

/*
Using dynamic programming (one array)
*/
class Solution {
    public:
    int uniquePaths(int m, int n) {
        if (m > n) return uniquePaths(n, m);
        vector<int> cur(m, 1);
        for (int j = 1; j < n; j++)
            for (int i = 1; i < m; i++)
                cur[i] += cur[i - 1]; 
        return cur[m - 1];
    }
}; 

/*
Using dynamic programming
*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        int a[m][n];
        
        for(int i=0; i<m; i++) {
            a[i][0] = 1;
        }
        
        for(int i=0; i<n; i++) {
            a[0][i] = 1;
        }
        
        for (int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                a[i][j]=a[i-1][j] + a[i][j-1];
            }
        }
        return a[m-1][n-1];
    }
};
