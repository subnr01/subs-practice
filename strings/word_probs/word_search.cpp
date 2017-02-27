/*
Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those
horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.

Tags: backtracking.

*/


class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (search(board, i, j, word.c_str()))
                    return true;
        return false;
    }
private: 
    bool search(vector<vector<char>>& board, int r, int c, const char* word) {
        if (!word[0]) return true;
        int m = board.size(), n = board[0].size();
        if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != word[0]) return false;
        board[r][c] = '$';
        if (search(board, r - 1 ,c, word + 1) || search(board, r + 1, c, word + 1) ||
            search(board, r, c - 1, word + 1) || search(board, r, c + 1, word + 1))
            return true;
        board[r][c] = word[0];
        return false;
    }
};
