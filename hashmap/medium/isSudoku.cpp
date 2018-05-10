/*

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.

*/



class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool row[9][9] = {false};
        bool col[9][9] = {false};
        bool box[9][9] = {false};
        
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] != '.') {
                int num = board[i][j] - '0' - 1;
                int k = i/3 * 3 + j/3;
                /* 
                the number index must not be in the row, col or box.
                Since our bool arrays are 9 in size, we do not really care
                about the board size.
                */
                if (row[i][num] || col[j][num] || box[k][num]) {
                    return false;
                }
                row[i][num] = col[j][num] = box[k][num] = true;
            }
            }
        }
        return true;
        
    }
};
