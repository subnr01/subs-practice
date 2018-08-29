




//BFS solution
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty())
        {
            return 0;
        }
        
        int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> totalDistance = grid;
        int result = -1;
        int walk = 0;
        for (int i = 0;i < m;i ++)
        {
            for (int j = 0;j < n;j ++)
            {
                if (grid[i][j] == 1)
                {
                    result = -1;
                    vector<vector<int>> distance = grid;
                    queue<pair<int, int>> q;
                    q.push(make_pair(i, j));
                    while (!q.empty())
                    {
                        pair<int, int> pr = q.front();
                        q.pop();
                        int ii = pr.first;
                        int jj = pr.second;
                        for (int k = 0;k < 4;k ++)
                        {
                            int newI = ii + direction[k][0];
                            int newJ = jj + direction[k][1];
                            if (newI >= 0 && newI < m && newJ >= 0 && newJ < n && grid[newI][newJ] == walk)
                            {
                                grid[newI][newJ] --;
                                distance[newI][newJ] = distance[ii][jj] + 1;
                                q.push(make_pair(newI, newJ));
                                totalDistance[newI][newJ] += (distance[newI][newJ] - 1);
                                if (result < 0 || totalDistance[newI][newJ] < result)
                                {
                                    result = totalDistance[newI][newJ];
                                }
                            }
                        }
                    }
                    
                    walk --;
                }
            }
        }
        
        return result;
    }
};
