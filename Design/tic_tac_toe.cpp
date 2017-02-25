/*


Design a Tic-tac-toe game that is played between two players on a n x n grid.

*/

//http://www.programcreek.com/2014/05/leetcode-tic-tac-toe-java/



class TicTacToe {
private:
    //count parameter: player 1 + : player 2: -
    vector<int> rowJudge;
    vector<int> colJudge;
    int diag, anti;
    int total;
public:
    /** Initialize your data structure here. */

    TicTacToe(int n):total(n), rowJudge(n), colJudge(n),diag(0),anti(0){}

    int move(int row, int col, int player) {
        int add = player == 1 ? 1 : -1;
        diag += row == col ? add : 0;
        anti += row == total - col - 1 ? add : 0;
        rowJudge[row] += add;
        colJudge[col] += add;
        if(abs(rowJudge[row]) == total || abs(colJudge[col]) == total || abs(diag) == total || abs(anti) == total) 
            return player;
        return 0;
    }
};


//Another solution
class TicTacToe {
public:
    TicTacToe(int n) : sz(n) {
        rows.resize(n, 0), cols.resize(n, 0);
        diagonal = anti_diagonal = 0;
    }
    
    int move(int row, int col, int player) {
        if (player == 1) {
            ++rows[row], ++cols[col];
            if (row == col)
                ++diagonal;
            if (row == sz - 1 - col)
                ++anti_diagonal;
            if (rows[row] == sz || cols[col] == sz || diagonal == sz || anti_diagonal == sz)
                return 1;
        }
        else {
            --rows[row], --cols[col];
            if (row == col)
                --diagonal;
            if (row == sz - 1 - col)
                --anti_diagonal;
            if (rows[row] == -sz || cols[col] == -sz || diagonal == -sz || anti_diagonal == -sz)
                return 2;
        }
        return 0;
    }

private:
    vector<int> rows, cols;
    int diagonal, anti_diagonal;
    int sz;
};



//stefan
public class TicTacToe {

    public TicTacToe(int n) {
        count = new int[6*n][3];
    }
    
    public int move(int row, int col, int player) {
        int n = count.length / 6;
        for (int x : new int[]{row, n+col, 2*n+row+col, 5*n+row-col})
            if (++count[x][player] == n)
                return player;
        return 0;
    }
    
    int[][] count;
}

