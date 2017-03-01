/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
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
            for(int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }
        /* the following code sets the first row to 0*/
        if(row){
            for(int j = 0; j < matrix[0].size(); j++) {
                matrix[0][j] = 0;
            }
        }
    }
};
