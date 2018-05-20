/*
Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

*/

http://www.programcreek.com/2014/05/leetcode-valid-sudoku-java/


class Solution {
public:

    bool isValidSudoku(vector<vector<char>>& board) {
        bool row[9][9] = {false}, col[9][9] = {false}, box[9][9] = {false};
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0' - 1, k = i / 3 * 3 + j / 3;
                    if (row[i][num] || col[j][num] || box[k][num]) return false;
                    row[i][num] = col[j][num] = box[k][num] = true;
                }
            }
        }
        return true;
    }
};
