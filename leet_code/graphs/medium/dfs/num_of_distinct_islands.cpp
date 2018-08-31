


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
