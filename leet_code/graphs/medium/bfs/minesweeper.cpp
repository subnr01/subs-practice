



class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
    deque<pair<int, int>> q({ { click[0], click[1] } });
    while (!q.empty()) {
        auto c = q.front().first, r = q.front().second, mines = 0;
        vector<pair<int, int>> neighbours;
        if (board[c][r] == 'M') board[c][r] = 'X';
        else for (auto i = -1; i <= 1; ++i) {
            for (auto j = -1; j <= 1; ++j) {
                if (c + i >= 0 && r + j >= 0 && c + i < board.size() && r + j < board[0].size()) {
                    if (board[c + i][r + j] == 'M') ++mines;
                    else if (mines == 0 && board[c + i][r + j] == 'E') neighbours.push_back({ c + i, r + j});
                }
            }
        }
        if (mines > 0) board[c][r] = '0' + mines;
        else for (auto n : neighbours) {
            board[n.first][n.second] = 'B';
            q.push_back(n);
        }
        q.pop_front();
    }
    return board;
}
};


//dfs
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

class Solution {
public:
    int rSiz, cSiz;
    vector<vector<int>> mnum;
    
    // only this function can be called on M, E!! 
    bool dfs(vector<vector<char>>& board, int y, int x) {
        if(board[y][x]=='M') {
            board[y][x] = 'X';
            return true;
        }
        if(!mnum[y][x]) {
            board[y][x]='B';
            for(int i=0; i<8; ++i) {
                int ty=y+dy[i], tx=x+dx[i];
                if(0<=ty && ty<rSiz && 0<=tx && tx<cSiz && board[ty][tx]=='E'){
                    bool b = dfs(board, ty, tx);
                    if(b) return true;
                }
            }
        } else {
            board[y][x]=mnum[y][x]+'0';
        }
        
        return false;
    }
    
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        rSiz = board.size(), cSiz = board[0].size();
        mnum = vector<vector<int>> (rSiz, vector<int>(cSiz,0));
        for(int i=0; i<rSiz; ++i) for(int j=0; j<cSiz; ++j) {
            int m = 0;
            if(board[i][j]=='M') {
                mnum[i][j]=-1;
                continue;
            }
            for(int c = 0; c<8; ++c) {
                int ty = i+dy[c], tx = j+dx[c];
                if(ty<0 || ty>=rSiz || tx<0 || tx>=cSiz) continue;
                if(board[ty][tx]=='M') m++;
            }
            mnum[i][j] = m;
        }
        dfs(board, click[0], click[1]);
        return board;
    }
};
