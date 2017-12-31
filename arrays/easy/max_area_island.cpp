/*
Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) 
connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)


*/


  class Solution {
public:
   int maxAreaOfIsland(vector<vector<int>>& grid) {
        int max_area = 0;
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                if(grid[i][j] == 1) {
                    max_area = max(max_area, AreaOfIsland(grid, i, j));
                }
            }
        }
        return max_area;
    }
    
    int AreaOfIsland(vector<vector<int>>& grid, int i, int j){
        if( i >= 0 && i < grid.size() && 
           j >= 0 && j < grid[0].size() && 
            grid[i][j] == 1) {
            grid[i][j] = 0;
            int a = AreaOfIsland(grid, i+1, j);
            int b = AreaOfIsland(grid, i-1, j);
            int c = AreaOfIsland(grid, i, j+1);
            int d = AreaOfIsland(grid, i, j-1);
            
            return 1 + a + b + c + d;
        }
        return 0;
    }
};
