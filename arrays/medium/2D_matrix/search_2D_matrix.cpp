Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) {
            return false;
        }
        int n = matrix[0].size();
        
        int low = 0;
        
        //This gives the highest index in the array.
        //DO NOT FORGET THIS
        int high = m*n - 1;
        
        while (low <= high)
        {
            int mid = (low + high)/2;
            
            //Notice the calculations here (how only n is used)
            int midX = mid / n;
            int midY = mid % n;
            
            if (matrix[midX][midY] == target)
            {
                return true;
            } 
            else if (matrix[midX][midY] > target)
            {
                high = mid - 1;
            } 
            else if (matrix[midX][midY] < target)
            {
                low = mid + 1;
            }
        }
        
        return false;
    }
};
