


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


//BFS slower
class Solution {
public:
   vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
    int numDistinctIslands(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        set<vector<pair<int, int>>> res;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 1) continue;
                vector<pair<int, int>> v;
                queue<pair<int, int>> q{{{i, j}}};
                grid[i][j] *= -1;
                while (!q.empty()) {
                    auto t = q.front(); q.pop();
                    for (auto dir : dirs) {
                        int x = t.first + dir[0], y = t.second + dir[1];
                        if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] <= 0) continue;
                        q.push({x, y});
                        grid[x][y] *= -1;
                        v.push_back({x - i, y - j});
                    }
                }
                res.insert(v);
            }
        }
        return res.size();
    }
};
