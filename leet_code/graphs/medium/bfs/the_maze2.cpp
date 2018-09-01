class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<int>> dist;
        dist.resize(maze.size());
        for (auto & e : dist)
            e.resize(maze[0].size(), INT_MAX);
        
        dist[start[0]][start[1]] = 0;
        
        vector<vector<int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        queue<vector<int>> q;
        q.push(start);
        
        while (!q.empty()) {
            auto front = q.front();
            q.pop();
            
            for (auto & d : dirs) {
                auto x = front[0] + d[0];
                auto y = front[1] + d[1];
                
                int count = 0;
                
                while (x >= 0 && y >= 0 && x < maze.size() && y < maze[0].size() && maze[x][y] == 0) {
                    x += d[0];
                    y += d[1];
                    count++;
                }
                
                if (dist[front[0]][front[1]] + count < dist[x-d[0]][y-d[1]]) {
                    dist[x-d[0]][y-d[1]] = dist[front[0]][front[1]] + count;
                    q.push({x-d[0], y-d[1]});
                }
            }
        }
        
        return dist[destination[0]][destination[1]] == INT_MAX ? -1 : dist[destination[0]][destination[1]];
    }
};
