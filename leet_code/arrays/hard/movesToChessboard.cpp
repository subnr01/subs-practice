/*

An N x N board contains only 0s and 1s. In each move, you can swap any 2 rows with each other, 
or any 2 columns with each other.

What is the minimum number of moves to transform the board into a "chessboard" - a board 
where no 0s and no 1s are 4-directionally adjacent? If the task is impossible, return -1.

Examples:
Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
Output: 2
Explanation:
One potential sequence of moves is shown below, from left to right:

0110     1010     1010
0110 --> 1010 --> 0101
1001     0101     1010
1001     0101     0101

The first move swaps the first and second column.
The second move swaps the second and third row.


Input: board = [[0, 1], [1, 0]]
Output: 0
Explanation:
Also note that the board with 0 in the top left corner,
01
10

is also a valid chessboard.

Input: board = [[1, 0], [1, 0]]
Output: -1
Explanation:
No matter what sequence of moves you make, you cannot end with a valid chessboard.

*/

//https://leetcode.com/problems/transform-to-chessboard/discuss/114847/Easy-and-Concise-Solution-with-Explanation-C++JavaPython

// THE GOAL IS TO FIND THE MINIMUM NUMBER OF MOVES TO TRANSFORM INTO CHESS BOARD.
// SINCE WE DO NOT KNOW THE FIRST CELL IS BLACK OR WHITE, WE start with both
// black and then we start with white and then compare


//slower but unlike complex the other sol
class Solution {
public:
   void swap_cols(vector<vector<int>> &board, int c1, int c2){
        int n = board.size();
        for(int i=0;i<n;i++){
            swap(board[i][c1], board[i][c2]);
        }
    }
    
    void swap_rows(vector<vector<int>> &board, int r1, int r2){
        int n = board.size();
        for(int i=0;i<n;i++){
            swap(board[r1][i], board[r2][i]);
        }
    }
    
    bool verify(vector<vector<int>> &board){
        int n = board.size();
        int b = board[0][0];
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if((i+j)%2 == 0 && board[i][j] != b) return false;
                if((i+j)%2 != 0 && board[i][j] == b) return false;
            }
        }
        
        return true;
    }
    
    int can_cols_swap(vector<vector<int>> board, int black){
        int n = board.size();
        vector<int> blks, whites;
        int moves = 0;
        for(int i=0;i<n;i++){
            if(board[0][i] == black && i%2 != 0) blks.push_back(i);
            if(board[0][i] != black && i%2 == 0) whites.push_back(i);
        }

        if(blks.size() == whites.size()){
            moves += blks.size();

            for(int i=0;i<blks.size();i++){
                swap_cols(board, blks[i], whites[i]);
            }
            if(!verify(board)) moves = INT_MAX;
        }else moves = INT_MAX;
        
        return moves;
    }
    
    int can_rows_swap(vector<vector<int>> board, int black){
        int moves = 0, n=board.size();
        // the below two vector contains row numbers
        // we do not want to swap two rows with the same color cell
        // as the first cell
        vector<int> blks, whites;
        for(int i=0;i<n;i++){
            if(board[i][0]==black && i%2 != 0) blks.push_back(i);
            if(board[i][0] != black && i%2 == 0) whites.push_back(i);
        }
        
        if(blks.size() == whites.size()){
            moves += blks.size();

            for(int i=0;i<blks.size();i++){
                swap_rows(board, blks[i], whites[i]);
            }

            int col_moves = min(can_cols_swap(board, 0), can_cols_swap(board, 1));
            if(col_moves == INT_MAX) moves = INT_MAX;
            else moves += col_moves;
        }else moves = INT_MAX;
        
        return moves;
    }
    
    int movesToChessboard(vector<vector<int>>& board) {
        int ans = min(can_rows_swap(board, 0), can_rows_swap(board, 1));
        return ans == INT_MAX ? -1 : ans;
    }

};



//94%
class Solution {
public:
    int movesToChessboard(vector<vector<int>>& b) {
        int N = b.size(); 
        int rowSum = 0; 
        int colSum = 0; 
        int rowSwap = 0; 
        int colSwap = 0;
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (b[0][0]^b[i][0]^b[0][j]^b[i][j]) {
                    return -1;
                }
            }
        }
        
        for (int i = 0; i < N; ++i) {
            rowSum += b[0][i];
            colSum += b[i][0];
            rowSwap += b[i][0] == i % 2;
            colSwap += b[0][i] == i % 2;
        }
        
        if (N / 2 > rowSum || rowSum > (N + 1) / 2) {
            return -1;
        }
        
        if (N / 2 > colSum || colSum > (N + 1) / 2) {
            return -1;
        }
        
        if (N % 2) 
        {
            if (colSwap % 2) {
                colSwap = N - colSwap;
            }
            if (rowSwap % 2) {
                rowSwap = N - rowSwap;
            } 
        } else {
            colSwap = min(N - colSwap, colSwap);
            rowSwap = min(N - rowSwap, rowSwap);
        }
        
        return (colSwap + rowSwap) / 2;
    }

};











