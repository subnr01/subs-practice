/*

A group of two or more people wants to meet and minimize the total travel distance. 
You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. 
The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

Example:

Input: 

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 6 

Explanation: Given three people living at (0,0), (0,4), and (2,2):
             The point (0,2) is an ideal meeting point, as the total travel distance 
             of 2+2+2=6 is minimal. So return 6.


*/


class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        
        int NumOfRow = grid.size();
        int NumOfCol = grid[0].size();
        vector<int> rows;
        vector<int> cols;
        
        for(int indexOfRow = 0; indexOfRow < NumOfRow; indexOfRow++){
            for(int indexOfCol = 0; indexOfCol < NumOfCol; indexOfCol++){
                if(grid[indexOfRow][indexOfCol]){
                    rows.push_back(indexOfRow);
                    cols.push_back(indexOfCol);
                }
            }
        }
        
        // sort(rows.begin(), rows.end()); as this's already sorted 
        sort(cols.begin(), cols.end());
        
        int idealRow = rows[rows.size() / 2];
        int idealCol = cols[cols.size() / 2];
        
        int result = 0;
        
        for(auto row: rows)
            result += abs(row - idealRow);
        for(auto col: cols)
            result += abs(col - idealCol);

        return result;
    }
};
