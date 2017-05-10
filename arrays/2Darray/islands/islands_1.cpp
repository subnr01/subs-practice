/*
Given a 2-d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded
by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges 
of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

*/


public class Solution {
    char[][] g;
    public int numIslands(char[][] grid) {
        int islands = 0;
        g = grid;
        for (int i=0; i<g.length; i++)
            for (int j=0; j<g[i].length; j++)
                islands += sink(i, j);
        return islands;
    }
    int sink(int i, int j) {
        if (i < 0 || i == g.length || j < 0 || j == g[i].length || g[i][j] == '0')
            return 0;
        g[i][j] = '0';
        sink(i+1, j); sink(i-1, j); sink(i, j+1); sink(i, j-1);
        return 1;
    }
}


//Solution 2
public class Solution {
    public int numIslands(char[][] grid) {
        int islands = 0;
        for (int i=0; i<grid.length; i++)
            for (int j=0; j<grid[i].length; j++)
                islands += sink(grid, i, j);
        return islands;
    }
    int sink(char[][] grid, int i, int j) {
        if (i < 0 || i == grid.length || j < 0 || j == grid[i].length || grid[i][j] == '0')
            return 0;
        grid[i][j] = '0';
        for (int k=0; k<4; k++)
            sink(grid, i+d[k], j+d[k+1]);
        return 1;
    }
    int[] d = {0, 1, 0, -1, 0};
}



//Merging the islands: O(m*n)

public int numIslands(char[][] grid) {
    if(grid==null || grid.length==0||grid[0].length==0)
        return 0;
 
    int m = grid.length;
    int n = grid[0].length;
 
    int count=0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='1'){
                count++;
                merge(grid, i, j);
            }
        }
    }
 
    return count;
}
 
public void merge(char[][] grid, int i, int j){
    int m=grid.length;
    int n=grid[0].length;
 
    if(i<0||i>=m||j<0||j>=n||grid[i][j]!='1')
        return;
 
    grid[i][j]='X';
 
    merge(grid, i-1, j);
    merge(grid, i+1, j);
    merge(grid, i, j-1);
    merge(grid, i, j+1);
}


