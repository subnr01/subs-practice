/*
largestIsland
In a 2D grid of 0s and 1s, we change at most one 0 to a 1.

After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).

Example 1:

Input: [[1, 0], [0, 1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
Example 2:

Input: [[1, 1], [1, 0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 1.
Example 3:

Input: [[1, 1], [1, 1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 1.

*/



//A distribution not available
class Solution {
public:
    int N;
    int largestIsland(vector<vector<int>>& grid) {
        N = grid.size();
        //DFS every island and give it an index of island
        int index = 2, res = 0;
        unordered_map <int, int>area;
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                if (grid[x][y] == 1) {
                    area[index] = dfs(grid, x, y, index);
                    res = max(res, area[index++]);
                }
            }
        }
        //traverse every 0 cell and count biggest island it can conntect
        for (int x = 0; x < N; ++x) for (int y = 0; y < N; ++y) if (grid[x][y] == 0) {
            unordered_set<int> seen = {};
            int cur = 1;
            for (auto p : move(x, y)) {
                index = grid[p.first][p.second];
                if (index > 1 && seen.count(index) == 0) {
                    seen.insert(index);
                    cur += area[index];
                }
            }
            res = max(res, cur);
        }
        return res;
    }

    vector<pair<int, int>> move(int x, int y) {
        vector<pair<int, int>> res;
        for (auto p : vector<vector<int>> {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {
            if (valid(x + p[0], y + p[1]))
                res.push_back(make_pair(x + p[0], y + p[1]));
        }
        return res;
    }

    int valid(int x, int y) {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    int dfs(vector<vector<int>>& grid, int x, int y, int index) {
        int area = 0;
        grid[x][y] = index;
        for (auto p : move(x, y))
            if (grid[p.first][p.second] == 1)
                area += dfs(grid, p.first, p.second, index);
        return area + 1;
    }
};
