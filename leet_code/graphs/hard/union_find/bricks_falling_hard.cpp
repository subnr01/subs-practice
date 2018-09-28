/*

We have a grid of 1s and 0s; the 1s in a cell represent bricks. 
A brick will not drop if and only if it is directly connected to the top of the grid, or at
least one of its (4-way) adjacent bricks will not drop.

We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j),
the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.

Return an array representing the number of bricks that will drop after each erasure in sequence.

Example 1:
Input: 
grid = [[1,0,0,0],[1,1,1,0]]
hits = [[1,0]]
Output: [2]
Explanation: 
If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.
Example 2:
Input: 
grid = [[1,0,0,0],[1,1,0,0]]
hits = [[1,1],[1,0]]
Output: [0,0]
Explanation: 
When we erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to the last move. So each erasure will cause no bricks dropping.  Note that the erased brick (1, 0) will not be counted as a dropped brick.

*/

class Solution {
public:
    class dsu {
        public:
        vector<int> parent;
        vector<int> rank;
        vector<int> size;
       
        dsu(int n)
        {
            for (int i = 0; i < n; i++)
                parent.push_back(i);
            rank.resize(n, 0);
            size.resize(n, 1);
        }
        
        int find(int i)
        {
            while (parent[i] != i)
                i = parent[i];
            return parent[i];
        }
        
        void uni(int i, int j)
        {
            int pi = find(i);
            int pj = find(j);
            
            if (pi == pj)
                return;
            if (rank[pi] >= rank[pj])
            {
                parent[pj] = pi;
                size[pi] += size[pj];
                if (rank[pi] == rank[pj])
                    rank[pi]++;
            }
            else
            {
                parent[pi] = pj;
                size[pj] += size[pi];                
            }
            
        }
        
        // return the size of virtual node
        int top()
        {
            // not include the virtual node itself
            return size[find(size.size()-1)]-1;
        }
    };
    
    
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int m = grid.size();
        if (!m)
            return vector<int>();
        int n = grid[0].size();
        
        vector<int> ans(hits.size(), 0);
        vector<vector<int>> A = grid;
        
        dsu dsu_obj(m*n+1);
        int d[5] = {-1, 0, 1, 0, -1};
        
        for (auto &hit: hits) {
            A[hit[0]][hit[1]] = 0;
        }
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (A[i][j] == 0)
                    continue;
                if (i == 0)
                    dsu_obj.uni(i*n+j, m*n);
                if (i-1 >= 0 && A[i-1][j] == 1)
                    dsu_obj.uni(i*n+j, (i-1)*n+j);
                if (j-1 >= 0 && A[i][j-1] == 1)
                    dsu_obj.uni(i*n+j, i*n+j-1);
            }
        }
        
        for (int i = hits.size()-1; i >= 0; i--)
        {
            int h_x = hits[i][0];
            int h_y = hits[i][1];
            if (grid[h_x][h_y] == 0) {
                continue;
            }
            
            int preTop = dsu_obj.top();
            A[h_x][h_y] = 1;
            
            if (h_x == 0) {
                dsu_obj.uni(h_x*n+h_y, m*n);
            }
            
            for (int k = 0; k < 4; k++)
            {
                int x = h_x + d[k];
                int y = h_y + d[k+1];
                if (x >= 0 && x < m && y >= 0 && y < n && A[x][y] == 1)
                    dsu_obj.uni(h_x*n+h_y, x*n+y);
            }
            
            int postTop = dsu_obj.top();
            ans[i] = max(postTop - preTop-1, 0);
        }
        return ans;
    }
    
};
