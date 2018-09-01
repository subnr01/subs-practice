/*

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. 
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3

*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) 
        {
            return 0;
        }
        int count = 0;
        vector<vector<char>> test;
        test = grid;
        
        int row = test.size();
        int col = test[0].size();
        
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if (test[i][j] == '1') {
                    count++;
                    merge(test, i, j);
                }
            }
        }
        return count;
        
    }
    
    
    void merge(vector<vector<char>>&test, int i, int j)
    {
        if(i == test.size() || j == test[0].size() || i < 0 || j < 0 || test[i][j] == '0') {
            return;
        }
        
        test[i][j] = '0';
        merge(test, i+1, j);
        merge(test, i, j+1);
        merge(test, i-1, j);
        merge(test, i, j-1);
    }
};


//BFS (slower)
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        set<pair<int, int>> visited;
        queue<pair<int, int>> q;
        vector<pair<int, int>> actions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[i].size(); j++){
                if(grid[i][j] == '1' && visited.count({i, j}) == 0){
                    res++;
                    visited.insert({i, j});
                    q.push({i, j});
                    while(!q.empty()){
                        pair<int, int> p = q.front(); q.pop();
                        for(int k = 0; k < actions.size(); k++){
                            int r_new = p.first + actions[k].first;
                            int c_new = p.second + actions[k].second;
                            if(0 <= r_new && r_new < grid.size() && 0 <= c_new && c_new < grid[0].size()){
                                if(grid[r_new][c_new] == '1' && visited.count({r_new, c_new}) == 0){
                                    visited.insert({r_new, c_new});
                                    q.push({r_new, c_new});
                                }
                            }
                        }
                    }
                }
            }
        }
        return res;
    }
};
