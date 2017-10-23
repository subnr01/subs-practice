/*

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].

*/

/*

The idea is just to add the elements in the spiral order. 
First the up-most row (u), then the right-most column (r), 
then the down-most row (d), and 
finally the left-most column (l). 
After finishing a row or a column, 
update the corresponding variable to continue the process.
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int m = matrix.size(), n = matrix[0].size();
        vector<int> spiral(m * n);
        int u = 0, 
        int d = m - 1; 
        int l = 0; 
        int r = n - 1; 
        int k = 0;
        while (true) {
            // left to right
            for (int col = l; col <= r; col++) spiral[k++] = matrix[u][col];
            if (++u > d) break;
            // up to down
            for (int row = u; row <= d; row++) spiral[k++] = matrix[row][r];
            if (--r < l) break;
            // right to left
            for (int col = r; col >= l; col--) spiral[k++] = matrix[d][col];
            if (--d < u) break;
            // down to up
            for (int row = d; row >= u; row--) spiral[k++] = matrix[row][l];
            if (++l > r) break;
        }
        return spiral;
    }
};
