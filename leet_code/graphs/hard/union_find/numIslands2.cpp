/*
A 2d grid map of m rows and n columns is initially filled with water. We may perform an 
addLand operation which turns the water at position (row, col) into a land. Given a list of 
positions to operate, count the number of islands after each addLand operation. An island is 
surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
You may assume all four edges of the grid are all surrounded by water.

Example:

Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
Output: [1,1,2,3]
Explanation:

Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0

*/


//Solution 2 (64 ms)
class Solution {
public:
   vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) 
   {
        vector<int> res;
        roots = vector<int>(m * n, -1);
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int islands = 0;
        for (auto pos : positions) 
        {
            int x = pos.first;
            int y = pos.second;
            int idx_p = x * n + y;
            roots[idx_p] = idx_p;
            ++islands;
            for (auto dir : dirs) 
            {
                int row = x + dir.first; 
                int col = y + dir.second;
                int idx_new = row * n + col;
                if (row >= 0 && row < m && col >= 0 && col < n && roots[idx_new] != -1) {
                    int rootNew = findRoot(idx_new);
                    int rootPos = findRoot(idx_p);
                    if (rootPos != rootNew) 
                    {
                        roots[rootPos] = rootNew;
                        --islands;
                    }
                }
            }
            res.push_back(islands);
        }
        return res;
    }
    
    int findRoot(int idx) 
    {
        while(idx != roots[idx]) 
        {
            roots[idx] = roots[roots[idx]]; 
            idx = roots[idx];
        }
        return idx;
    }
    
private:
    vector<int> roots;
    
};
==============================================================================

//Standard solution
class UnionFind
{
public:
    UnionFind(const int &n)
    {
        count = 0;
        for(int i = 0; i < n; ++i)
        {
            parent.emplace_back(-1);
            rank.emplace_back(0);
        }
    }
        
    int getCount() const
    {
        return count;
    }
        
    bool isValid(const int &i) const
    {
        return (parent[i] >= 0);
    }
        
    void setParent(const int &i)
    {
        parent[i] = i;
        ++count;
    }
        
    int findParent(const int &i) // path compression
    {
        if(parent[i] != i)
        {
            parent[i] = findParent(parent[i]);
        }
        
        return parent[i];
    }
        
    void unionWithRank(const int &x, const int &y)
    {
        int rootx = findParent(x);
        int rooty = findParent(y);
        
        if(rootx != rooty)
        {
            if(rank[rootx] < rank[rooty])
            {
                parent[rootx] = rooty;
            }
            else if (rank[rootx] > rank[rooty])
            {
                parent[rooty] = rootx;
            }
            else
            {
                parent[rooty] = rootx;
                ++rank[rootx];
            }
             
            --count;
        }
    }
    
private:
    vector<int> parent;
    vector<int> rank;
    int count; // the number of connected components
    
};
class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        vector<int> results;
        UnionFind uf(m * n);
        
        for(auto &&pos : positions)
        {
            int r = pos.first;
            int c = pos.second;
            
            vector<int> overlap;
            if((r -1) >= 0 && uf.isValid((r-1) * n + c))
            {
                overlap.emplace_back((r-1)*n + c);
            }
            
            if((r+1) < m && uf.isValid((r+1) * n + c))
            {
                overlap.emplace_back((r+1) * n + c);
            }
            
            if((c-1) >= 0 && uf.isValid(r * n + (c-1)))
            {
                overlap.emplace_back(r * n + (c-1));
            }
            
            if((c+1) < n && uf.isValid(r * n + (c+1)))
            {
                overlap.emplace_back(r * n + (c+1));
            }
            
            int index = r * n + c;
            uf.setParent(index);
            
            for(auto &&i : overlap)
            {
                uf.unionWithRank(i, index);
            }
            
            results. emplace_back(uf.getCount());
        }
        
        return results;
    }
};


==============================================================================


