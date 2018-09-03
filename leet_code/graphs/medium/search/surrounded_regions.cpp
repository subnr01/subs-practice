/*

Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X


*/

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0) {
            return;
        }
        
        connectBorder0s(board);
        
        for(int i=0; i < board.size(); i++){
            for(int j=0; j < board[0].size(); j++)
                if(board[i][j] != '1')
                    board[i][j] = 'X';
                else
                    board[i][j] = 'O';
        }
    }
    
    void connectBorder0s(vector<vector<char>>& board){
        int rows = board.size();
        int cols = board[0].size();
        
        for(int j=0; j < cols; j++){
            bfs(board, 0, j);
            bfs(board, rows-1, j);
        }
        
        for(int i=0; i < rows; i++){
            bfs(board, i, 0);
            bfs(board, i, cols-1);
        }
    }
    
    void bfs(vector<vector<char>>& board, int i, int j){
        if(i < board.size() && 
           j < board[0].size() && 
           i >= 0 && j >= 0 && 
           board[i][j] == 'O'){
            
            board[i][j] = '1';
            bfs(board, i+1, j);
            bfs(board, i-1, j);
            bfs(board, i, j+1);
            bfs(board, i, j-1);
        }
    }
};
