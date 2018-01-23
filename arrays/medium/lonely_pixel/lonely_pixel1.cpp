/*

Given a picture consisting of black and white pixels, find the number of black lonely pixels.

The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.

A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.

Example:
Input: 
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

Output: 3
Explanation: All the three 'B's are black lonely pixels.


*/

/**
 * suppose matrix is m*n, there is at most min(m, n) lonely pixels, because there could be no more than 1 in each row, or column;
 * therefore, if we record num of black pixel on each row and column, we can easily tell whether each pixel is lonely or NO.
 *     _0_1_2_
 *  0 | 0 0 1   rows[0] = 1
 *  1 | 0 1 0   rows[1] = 1
 *  2 | 1 0 0   rows[2] = 1
 * 
 * cols[0][1][2]
 *     1  1  1
 */

//Related topics
//Array and Depth first search

class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) 
    {
        int m = picture.size();
        int n = picture[0].size();
        int count = 0;
        vector<int> rows(m, 0);
        vector<int> columns(n, 0);
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++) 
            {
                rows[i] += picture[i][j] == 'B';
                columns[j] += picture[i][j] == 'B';
            }
        }
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++) 
            {
                count += picture[i][j] == 'B' ? rows[i] == 1 && columns[j] == 1: 0;
            }           
        }
        
        return count;
    }
};
