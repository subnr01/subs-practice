
/*

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no 
two queens attack each other.

Given an integer n, return the total number of distinct solutions.

*/


//My solution: clean and simple
class Solution {
public:
    int totalNQueens(int n) {
        int count = 0;
        vector<string> nQueens (n, string(n,'.'));
        nQue(count, nQueens, 0, n);
        return count;
        
    }
    void nQue(int &count, vector<string> &nQueens, int row, int n)
    {
        if (row == n) 
        {
            count++;
            return;
        }
        
        for (int col = 0; col < n; col++)
        {
            if (isValid(nQueens, row, col, n)) 
            {
                nQueens[row][col] = 'Q';
                nQue(count, nQueens, row + 1, n);
                nQueens[row][col] = '.';
            }
        }
    }
    
    
    bool isValid(vector<string> &nQueens, int row, int col, int n)
    {
        int i = 0;
        int j = 0;
        
        for (i = 0; i < row; i++)
        {
            if (nQueens[i][col] == 'Q') {
                return false;
            }
        }
        
        for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (nQueens[i][j] == 'Q') {
                return false;
            }
        }
        
        
        for (i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        {
            if (nQueens[i][j] == 'Q') {
                return false;
            }
        }
        
        return true;
    }
};


//Another solution
class Solution {
public:
    int totalNQueens(int n) {
    vector<bool> col(n, true);
    vector<bool> anti(2*n-1, true);
    vector<bool> main(2*n-1, true);
    vector<int> row(n, 0);
    int count = 0;
    dfs(0, row, col, main, anti, count);
    return count;
}
void dfs(int i, vector<int> &row, vector<bool> &col, vector<bool>& main, vector<bool> &anti, int &count) {
        if (i == row.size()) {
            count++;
            return;
        }
       for (int j = 0; j < col.size(); j++) {
         if (col[j] && main[i+j] && anti[i+col.size()-1-j]) {
             row[i] = j; 
             col[j] = main[i+j] = anti[i+col.size()-1-j] = false;
             dfs(i+1, row, col, main, anti, count);
             col[j] = main[i+j] = anti[i+col.size()-1-j] = true;
      }
    }
}
};
