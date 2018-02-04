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
        int m = grid.size(), n = grid[0].size();
        set<vector<vector<int>>> islands;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vector<vector<int>> island;
                if (dfs(i, j, i, j, grid, m, n, island))
                    islands.insert(island);
            }
        }
        return islands.size();
    }

private:
    int delta[4][2] = { 0, 1, 1, 0, 0, -1, -1, 0};

    bool dfs(int i0, int j0, int i, int j, vector<vector<int>>& grid, int m, int n, vector<vector<int>>& island) {
        if (i < 0 || m <= i || j < 0 || n <= j || grid[i][j] <= 0) return false;
        island.push_back({i - i0, j - j0});
        grid[i][j] *= -1;
        for (int d = 0; d < 4; d++) {
            dfs(i0, j0, i + delta[d][0], j + delta[d][1], grid, m, n, island);
        }
        return true;
    }
};
