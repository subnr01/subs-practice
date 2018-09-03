/*
There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by 
rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, 
it could choose the next direction.

Given the ball's start position, the destination and the maze, determine whether the ball could stop 
t the destination.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may 
assume that the borders of the maze are all walls. The start and destination coordinates are represented 
by row and column indexes.

Example 1

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (4, 4)
Output:true


Example 2

Input 1: a maze represented by a 2D array

0 0 1 0 0
0 0 0 0 0
0 0 0 1 0
1 1 0 1 1
0 0 0 0 0

Input 2: start coordinate (rowStart, colStart) = (0, 4)
Input 3: destination coordinate (rowDest, colDest) = (3, 2)

Output: false
Explanation: There is no way for the ball to stop at the destination.

*/






//BFS
 bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if (maze.empty() || maze[0].empty()) return true;
        int m = maze.size(), n = maze[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        queue<pair<int, int>> q;
        q.push({start[0], start[1]});
        visited[start[0]][start[1]] = true;
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            if (t.first == destination[0] && t.second == destination[1]) return true;
            for (auto dir : dirs) {
                int x = t.first, y = t.second;
                while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 0) {
                    x += dir[0]; y += dir[1];
                }
                x -= dir[0]; y -= dir[1];
                if (!visited[x][y]) {
                    visited[x][y] = true;
                    q.push({x, y});
                }
            }
        }
        return false;
    }
};

  
//Another soln
  class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        auto visited = vector<vector<bool>>(maze.size(), vector<bool>(maze.front().size()));
        queue<pair<int, int>> q;
        q.push({start[0], start[1]});
        visited[start[0]][start[1]] = true;
        pair<int,int> dest{destination[0], destination[1]};
        while (not q.empty()) {
            if (dest == q.front()) {
                return true;
            }
            int ci = q.front().first;
            int cj = q.front().second;
            q.pop();
            int i, j;
            // top
            i = ci; j = cj;
            while (i >= 0 and maze[i][j] == 0) { i--; } i++;
            if (i >= 0 and not visited[i][j]) { q.push({i, j}); visited[i][j] = true; }
            // bottom
            i = ci; j = cj;
            while (i < maze.size() and maze[i][j] == 0) { i++; } i--;
            if (i < maze.size() and not visited[i][j]) { q.push({i, j}); visited[i][j] = true; }
            // left
            i = ci; j = cj;
            while (j >= 0 and maze[i][j] == 0) { j--; } j++;
            if (j >= 0 and not visited[i][j]) { q.push({i, j}); visited[i][j] = true; }
            // bottom
            i = ci; j = cj;
            while (j < maze.front().size() and maze[i][j] == 0) { j++; } j--;
            if (j < maze.front().size() and not visited[i][j]) { q.push({i, j}); visited[i][j] = true; }

        }
        return false;
    }
};

//BFS
class Solution {
public:
    // only decide if the destination could be reached, no need to struggling to search for the shortest path
    // should not change the maze
    // don't need to research the position if it has been visited, as we don't need to search for the shortest path
    bool bfs(vector<vector<int>> maze, vector<int> start, vector<int> destination)
    {
        queue<pair<int,int>> q;
        q.push(pair<int,int>(start[0], start[1]));
        int row=maze.size();
        int col=maze[0].size();
        
        // four directions
        vector<pair<int,int>> dr{{-1,0}, {0,-1}, {0,1}, {1,0}};
        // visited map
        vector<vector<char>> visited(row, vector<char>(col, 0));
        // mark starting position as visited
        visited[start[0]][start[1]]=1;

        
        while(!q.empty())
        {
            // pop out from queue
            pair<int, int> tmp=q.front();
            // mark current cell as visited
            visited[tmp.first][tmp.second]=1;
            
            // four direction search
            for(int i=0; i<4; i++)
            {
                int x=tmp.first;
                int y=tmp.second;
                int d_x=dr[i].first;
                int d_y=dr[i].second;
                while(x+d_x>=0 && x+d_x<row && y+d_y>=0 && y+d_y<col && maze[x+d_x][y+d_y]==0)
                {
                    x += d_x;;
                    y += d_y;
                }
                
                if(x==destination[0]&&y==destination[1])
                    return true;
                else if(visited[x][y]==0)
                    q.push(pair<int,int>(x,y));
            }
            
            // pop out current node
            q.pop();
        }
        
        // if cannot find the destination, return false
        return false;
    }
    
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        if(maze.empty()||start.empty()||destination.empty())
            return false;
        return bfs(maze, start, destination);
    }
};
