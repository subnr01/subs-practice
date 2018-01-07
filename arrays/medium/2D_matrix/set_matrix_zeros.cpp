/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
*/


/*
Logic:

If the element of the matrix is 0, then set the first element in the same row to 0
and set the first element in the same column to 0.
If it is actually the first element in the corresponding row or column, then 
mark them as visited.

Traverse the matrix again in a normal way and if you find that the first element
in the row or column is set to 0, then set all the elments to 0.

Now there is the special case of the visited, where the first element in the row
or column is zero. If you follow the above logic to this case, only the row
or column is set to 0 and not both. So this is need to be handled as a 
seperate case.

If visited was the first element of a col, then set all the elements of that col to 0
and vice versa.

*/


class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool row = false, col = false;
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                if(matrix[i][j] == 0) {
                    if(i == 0) row = true;
                    if(j == 0) col = true;
                    matrix[0][j] = matrix[i][0] = 0;
                }
            }
        }
        
        /* This will set the corresponding row or column (other than the non first row/column to 0).*/
        for(int i = 1; i < matrix.size(); i++){
            for(int j = 1; j < matrix[0].size(); j++) {
              
                if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        
        /* the following code sets the first column to 0*/
        if(col){
            //Notice i is compared against number of rows.
            for(int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }
        /* the following code sets the first row to 0*/
        if(row){
            //Notice j is compared against the column size.
            for(int j = 0; j < matrix[0].size(); j++) {
                matrix[0][j] = 0;
            }
        }
    }
};
