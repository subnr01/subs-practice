/*

Refer leetcode

*/


//Sol1
class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
                /* BFS to comput distance array Time O(mn) space O(mn)*/
        int row = maze.size();
        int col = maze[0].size();
        int dist, x, y;
        int dirtx[4] = {0, 1, -1, 0};
        int dirty[4] = {1, 0, 0, -1};
        char dirtStr[4] = {'r', 'd', 'u', 'l'};
        queue<pair<int, int>> points;
        vector<vector<int>> dists(row, vector<int>(col, INT_MAX));
        unordered_map<int, string> paths;
        string path;
        
        dists[ball[0]][ball[1]] = 0;
        points.push({ball[0], ball[1]});
        
        while (!points.empty()) {
            auto p = points.front();
            points.pop();
            
            for (int d = 0; d < 4; ++d) {
                x = p.first;
                y = p.second;
                dist = dists[x][y];
                path = paths[x * col + y];
                
                while (x + dirtx[d] >= 0 && x + dirtx[d] < row &&
                       y + dirty[d] >= 0 && y + dirty[d] < col &&
                       maze[x + dirtx[d]][y + dirty[d]] == 0) {
                    ++dist;
                    x += dirtx[d];
                    y += dirty[d];
                    if (x == hole[0] && y == hole[1]) break;
                }

                path.push_back(dirtStr[d]);
                if (dists[x][y] > dist ||
                    (dists[x][y] == dist && paths[x * col + y].compare(path) > 0)) {
                    dists[x][y] = dist;
                    paths[x * col + y] = path;
                    if (x != hole[0] || y != hole[1]) points.push({x, y});
                }
            }
        }
        
        return dists[hole[0]][hole[1]] == INT_MAX ? "impossible" : paths[hole[0] * col + hole[1]];
    }
};


//Sol2
class Solution {
public:
    string roll(vector<vector<int>>& maze, int rowBall, int colBall, const vector<int>& hole, 
    int d_row, int d_col, int steps, const string& path, pair<string, int>& res)
{
    if (steps < res.second) {
        if (d_row != 0 || d_col != 0) { // both are zero for the initial ball position.
            while ((rowBall + d_row) >= 0 && (colBall + d_col) >= 0 && (rowBall + d_row) <  maze.size() 
                && (colBall + d_col) < maze[0].size() && maze[rowBall + d_row][colBall + d_col] != 1) 
            {
                rowBall += d_row;
                colBall += d_col;
                ++steps;
                if (rowBall == hole[0] && colBall == hole[1] && steps < res.second) res = {path, steps};
            }
        }
        if (maze[rowBall][colBall] == 0 || steps + 2 < maze[rowBall][colBall]) {
            maze[rowBall][colBall] = steps + 2; // '1' is for the walls.
            if (d_row == 0) roll(maze, rowBall, colBall, hole, 1, 0, steps, path + "d", res);
            if (d_col == 0) roll(maze, rowBall, colBall, hole, 0, -1, steps, path + "l", res);
            if (d_col == 0) roll(maze, rowBall, colBall, hole, 0, 1, steps, path + "r", res);
            if (d_row == 0) roll(maze, rowBall, colBall, hole, -1, 0, steps, path + "u", res);
        }
    }
    return res.first;
}
string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) 
{
    return roll(maze, ball[0], ball[1], hole, 0, 0, 0, "", pair<string, int>() = {"impossible", INT_MAX});
}
};
