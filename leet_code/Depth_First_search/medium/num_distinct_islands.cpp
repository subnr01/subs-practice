/*

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island 
is considered to be the same as another if and only if 
one island can be translated (and not rotated or reflected) to equal the other.

Example 1:
11000
11000
00011
00011

Given the above grid map, return 1.
Example 2:
11011
10000
00001
11011


*/


class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        
        unordered_set<string> res;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    string path;
                    dfs(grid, i, j, path, 'o');
                    // cout << i << " " << j << " " << num << endl;
                    res.insert(path);
                }
            }
        }
        return res.size();
    }
    
    void dfs(vector<vector<int>>& grid, int row, int col, string& path, char dir) {
        if (row < 0 || row >= (int)grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] == 0) {
            return;
        }
        
        path.push_back(dir);
        grid[row][col] = 0;
        dfs(grid, row - 1, col, path, 'u');
        dfs(grid, row, col + 1, path, 'r');
        dfs(grid, row + 1, col, path, 'd');
        dfs(grid, row, col - 1, path, 'l');
        path.push_back('b');
    }
};
