/*
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
Empty cells are indicated by the character '.'.


*/


class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solveSudoku(board, 0, 0);
    }
    
    
    bool check(vector<vector<char>> &board, int i, int j, char val)
    {
        int row = i - i%3;
        int column = j - j%3;
        
        for(int x=0; x<9; x++) {
            if(board[x][j] == val) 
                return false;
        }
        
        for(int y=0; y<9; y++) {
            if(board[i][y] == val) 
                return false;
        }
        
        for(int x=0; x<3; x++) {
            for(int y=0; y<3; y++) {
                if(board[row+x][column+y] == val) 
                        return false;
            }
        }
        return true;
    }


    bool solveSudoku(vector<vector<char>> &board, int i, int j)
    {
        if(i==9) return true;
        if(j==9) return solveSudoku(board, i+1, 0);
        
        if(board[i][j] != '.') {
            /* Go to the next cell in the row */
            return solveSudoku(board, i, j+1);
        }
        
        /*
        Current cell is empty
        */
        for(char c='1'; c<='9'; c++)
        {
            if(check(board, i, j, c))
            {
                board[i][j] = c;
                
                if(solveSudoku(board, i, j+1)) {
                    /*
                    Satisfied both row and column
                    */
                    return true;
                }
                /* 
                satisfied the row, but
                did not satisfy the column
                */
                board[i][j] = '.';
            }
        }
        
        return false;
    }
    
};
