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