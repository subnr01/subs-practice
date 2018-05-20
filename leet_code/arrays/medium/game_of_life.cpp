/*
Given a board with m by n cells, each cell has an initial state live (1) or dead (0). 
Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the 
following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state.


*/



//First Version (stephen) 0(mn) and O(1) space
void gameOfLife(vector<vector<int>>& board) {
    int m = board.size(), n = m ? board[0].size() : 0;
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            int count = 0;
            for (int I=max(i-1, 0); I<min(i+2, m); ++I)
                for (int J=max(j-1, 0); J<min(j+2, n); ++J)
                    count += board[I][J] & 1;
            if (count == 3 || count - board[i][j] == 3)
                board[i][j] |= 2;
        }
    }
    for (int i=0; i<m; ++i)
        for (int j=0; j<n; ++j)
            board[i][j] >>= 1;
}



//Second version
class Solution {
public:
  
    void gameOfLife(vector<vector<int>>& board) {
    if (board.size() == 0) return;
    int m = board.size();
    if(board[0].size() == 0) return;
    int n  = board[0].size();
        
    for (int i =0 ; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int count = 0;
            for (int I = max(i-1, 0); I < min(i+2, m); ++I)
                for (int J = max(j-1, 0); J < min(j+2, n); ++J)
                    if(I != i || J != j) {
                        count += board[I][J] & 1;
        
                    }        
                        
            
            if ( ((board[i][j] & 1) == 0 && count == 3) || (((board[i][j] & 1) == 1 && (count == 2 || count == 3 )) ) )
                board[i][j] = board[i][j] | 2;
        }
    }
    for (int i=0; i<m; ++i)
        for (int j=0; j<n; ++j)
            board[i][j] >>= 1;
}
    
};
