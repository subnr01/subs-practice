/*

On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).

Now rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square 
to another 4-directionally adjacent square if and only if the elevation of both squares individually are
at most t. You can swim infinite distance in zero time. Of course, you must stay within the
boundaries of the grid during your swim.

You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?

Example 1:

Input: [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.

You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.
Example 2:

Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation:
 0  1  2  3  4
24 23 22 21  5
12 13 14 15 16
11 17 18 19 20
10  9  8  7  6

The final route is marked in bold.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.



*/

//Related optics: Heap, Binary search, DFS, union find

class Solution {
public:

    struct T {
        int t, x, y;
        T(int a, int b, int c) : t (a), x (b), y (c){}
        bool operator< (const T &d) const {return t > d.t;}
    };

    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size (), res = 0;
        priority_queue<T> pq;
        pq.push(T(grid[0][0], 0, 0));
        vector<vector<int>> seen(N, vector<int>(N, 0));
        seen[0][0] = 1;
        static int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, { -1, 0}};

        while (true) {
            auto p = pq.top ();
            pq.pop ();
            res = max(res, p.t);
            if (p.x == N - 1 && p.y == N - 1) return res;
            for (auto& d : dir) {
                int i = p.x + d[0], j = p.y + d[1];
                if (i >= 0 && i < N && j >= 0 && j < N && !seen[i][j]) {
                    seen[i][j] = 1;
                    pq.push (T(grid[i][j], i, j));
                }
            }
        }
    }
};


//dfs + binary_search
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int low = grid[0][0], hi = n*n-1;
        while (low < hi) {
            int mid = low + (hi-low)/2;
            if (valid(grid, mid)) 
               hi = mid;
            else
               low = mid+1;
        }
        return low;
    }
private:
    bool valid(vector<vector<int>>& grid, int waterHeight) {
        int n = grid.size();
        vector<vector<int>> visited(n, vector<int>(n, 0));
        vector<int> dir({-1, 0, 1, 0, -1});
        return dfs(grid, visited, dir, waterHeight, 0, 0, n);
    }
    bool dfs(vector<vector<int>>& grid, vector<vector<int>>& visited, vector<int>& dir, int waterHeight, int row, int col, int n) {
        visited[row][col] = 1;
        for (int i = 0; i < 4; ++i) {
            int r = row + dir[i], c = col + dir[i+1];
            if (r >= 0 && r < n && c >= 0 && c < n && visited[r][c] == 0 && grid[r][c] <= waterHeight) {
                if (r == n-1 && c == n-1) return true;
                if (dfs(grid, visited, dir, waterHeight, r, c, n)) return true;
            }
        }
        return false;
    }
};


//union find
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        ids = vector<vector<int>>(rows*cols, vector<int>{0, 0});
                vector<int> pos(rows*cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ids[i * cols + j][0] = i * cols + j;
                ids[i * cols + j][1] = 1;
                                pos[grid[i][j]] = i*cols + j;

            }
        }
        int ret = 0;
        for (ret = 0; ret < rows * cols; ret++) {
            int r = pos[ret] / cols;
            int c = pos[ret] % cols;
            if (r > 0 && grid[r - 1][c] < grid[r][c])
                ids[r*cols + c][0] = unite(findparent((r-1)*cols + c), findparent(r*cols + c));
            if (r < rows - 1 && grid[r+1][c] < grid[r][c]) {
                ids[r*cols + c][0] = unite(findparent((r+1)*cols + c), findparent(r*cols + c));
            }
            if (c > 0 && grid[r][c-1] < grid[r][c])
                ids[r*cols + c][0] = unite(findparent(r*cols + c - 1), findparent(r*cols + c));
            if (c < cols - 1 && grid[r][c+1] < grid[r][c])
                ids[r*cols + c][0] = unite(findparent(r*cols + c + 1), findparent(r*cols + c));

            if (findparent(rows*cols-1) == findparent(0)) break;
                    }
        return ret;
    }
private:
    vector<vector<int>> ids;
    int findparent(int n) {
        if (ids[n][0] == n) return n;
        ids[n][0] = findparent(ids[n][0]);
        return ids[n][0];
    }

    int unite(int n1, int n2) {
        if (ids[n1][1] > ids[n2][1]) {
            ids[n2][0] = n1;
            return n1;
        } else if (ids[n1][1] < ids[n2][1]) {
            ids[n1][0] = n2;
            return n2;
        } else {
            ids[n1][0] = n2;
            ids[n1][1] += 1;
            return n2;
        }
    }
};












