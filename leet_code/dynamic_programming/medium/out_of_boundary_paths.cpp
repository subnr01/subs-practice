/*

There is an m by n grid with a ball. Given the start coordinate (i,j) of the ball, you can move the 
ball to adjacent cell or cross the grid boundary in four directions (up, down, left, right). However, you can at most move N times. Find out the number of paths to move the ball out of grid boundary. 
The answer may be very large, return it after mod 109 + 7.
*/

Input:m = 2, n = 2, N = 2, i = 0, j = 0
Output: 6

//https://discuss.leetcode.com/topic/88492/c-6-lines-dp-o-n-m-n-6-ms/2

int findPaths(int m, int n, int N, int i, int j) {
    unsigned int g[2][50][50] = {};
    while (N-- > 0)
        for (auto k = 0; k < m; ++k)
            for (auto l = 0, nc = (N + 1) % 2, np = N % 2; l < n; ++l)
                g[nc][k][l] = ((k == 0 ? 1 : g[np][k - 1][l]) + (k == m - 1 ? 1 : g[np][k + 1][l])
                    + (l == 0 ? 1 : g[np][k][l - 1]) + (l == n - 1 ? 1 : g[np][k][l + 1])) % 1000000007;
    return g[1][i][j];
}

//optimised version
int findPaths(int m, int n, int N, int i, int j) {
    unsigned int g[50][50] = {}, r[50];
    while (N-- > 0)
        for (auto k = 0; k <= m; ++k)
            for (auto l = 0; l < n; ++l) {
                auto tmp = r[l];
                r[l] = (k == m ? 0 : ((k == 0 ? 1 : g[k - 1][l]) + (k == m - 1 ? 1 : g[k + 1][l])
                    + (l == 0 ? 1 : g[k][l - 1]) + (l == n - 1 ? 1 : g[k][l + 1])) % 1000000007);
                if (k > 0) g[k - 1][l] = tmp;
            }
    return g[i][j];
}
