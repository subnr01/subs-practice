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

//need to run again, to find which is faster

//Another union find
class UnionFind {
public:
    vector<int> parents, counts;
    UnionFind(int n)
    {
        parents.reserve(n);
        counts.reserve(n);
        for(int i = 0; i < n; ++i)
        {
            parents[i] = i;
            counts[i] = 1;
        }
        counts[0] = 0;
    }
    
    int Find(int a)
    {
        while(parents[a] != a)
        {
            parents[a] = parents[parents[a]];
            a = parents[a];
        }
        
        return a;
    }
    
    void Union(int a, int b)
    {
        if(a != b)
        {
            parents[a] = b;
            counts[b] += counts[a];
        }
    }
};

class Solution {
public:
    //O(M * N * hits.size()), O(M * N)
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        if(grid.empty() || grid[0].empty())
            return {};
        int m = grid.size(), n = grid[0].size();
        int mul = max(m, n) + 1;
        vector<vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        UnionFind uf(m * mul + 1);
        for(auto& hit : hits)
        {
            if(grid[hit[0]][hit[1]] == 1)
                grid[hit[0]][hit[1]] = -1;
        }
        
        auto validPos = [&](int i, int j)
        {
            return i >= 0 && i < m && j >= 0 && j < n;
        };

        function<void(int, int, int)> connect = [&](int r, int c, int p)
        {
            if(validPos(r, c) && grid[r][c] == 1)
            {
                grid[r][c] = 2;
                uf.Union(r * mul + c + 1, p);
                
                for (auto& dir : dirs)
                    connect(r + dir[0], c + dir[1], p);
            }
        };
        
        //All components connected to top
        for(int i = 0; i < n; ++i)
            connect(0, i, 0);

        //All other components
        for(int i = 1; i < m; ++i)
            for(int j = 0; j < n; ++j)
                connect(i, j, i * mul + j + 1);
        
        int len = hits.size();
        vector<int> res(len);
        for(int i = len - 1; i >= 0; --i)
        {
            int curCount = uf.counts[0];

            auto& hit = hits[i];
            if(grid[hit[0]][hit[1]] == -1)
            {
                grid[hit[0]][hit[1]] = 2;
                set<int> pset = {hit[0] * mul + hit[1] + 1};
                for (auto& dir : dirs)
                {
                    int newr = hit[0] + dir[0];
                    int newc = hit[1] + dir[1];
                    if (validPos(newr, newc) && grid[newr][newc] == 2)
                    {
                        int p = uf.Find(newr * mul + newc + 1);
                        pset.insert(p);
                    }
                }

                if (*pset.begin() <= n)
                {
                    for (auto& p : pset)
                        uf.Union(p, 0);
                    res[i] = uf.counts[0] - curCount - 1;
                }
                else
                {
                    for (auto& p : pset)
                        uf.Union(p, *pset.begin());
                }
            }
        }
        return res;
    }
};








//very long soln (slower of course)
struct Node{
    int rank, parent;
    Node():rank(1),parent(-1){};
};

class UF{
public:
    UF(int n){
        uf = vector<Node>(n);
    }
    int Find(int x){
        if(uf[x].parent < 0){
            return x;
        }
        int res = Find(uf[x].parent);
        uf[x].parent = res;
        return res;
    }
    int GetRank(int x){
        int parX = Find(x);
        return uf[parX].rank;
    }

    void Union(int x, int y){
        int parX = Find(x);
        int parY = Find(y);
        if(parX == parY){
            return;
        }

        if(uf[parX].rank > uf[parY].rank){
            uf[parY].parent = parX;
            uf[parX].rank += uf[parY].rank;
            uf[parY].rank = 1;
        }
        else{
            uf[parX].parent = parY;
            uf[parY].rank += uf[parX].rank;
            uf[parX].rank = 1;

        }
    }

    vector<Node> uf;
private:
};

class Solution {
public:
    vector<int> hitBricks(vector<vector<int>> grid, vector<vector<int>> hits) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> mat = grid;
        for(auto &hit: hits){
            int x = hit[0];
            int y = hit[1];
            mat[x][y] = 0;
        }

        vector<int> res;
        UF myUf(m*n+1);
        // get the last step union find
        // let m*n node is the roof node
        for(int j=0; j<n; ++j){
            if(mat[0][j] == 1){
                myUf.Union(j, m*n);
            }
        }

        for(int i=1; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(mat[i][j] == 1){
                    if(mat[i-1][j] == 1){
                        myUf.Union(i*n+j, (i-1)*n+j);
                    }
                    if(j-1>=0 && mat[i][j-1]==1){
                        myUf.Union(i*n+j, i*n+(j-1));
                    }
                }
            }
        }

        // put brick back
        for(int k = hits.size()-1; k>=0; --k){
            int x = hits[k][0];
            int y = hits[k][1];

            if(grid[x][y] == 1){
                int prevRoofRank = myUf.GetRank(m*n);
                mat[x][y] = 1;
                if(x+1<m && mat[x+1][y] == 1){
                   myUf.Union((x+1)*n+y, x*n+y);
                }
                if(x-1>=0 && mat[x-1][y] == 1){
                    myUf.Union((x-1)*n+y, x*n+y);
                }
                if(y+1<n && mat[x][y+1] == 1){
                    myUf.Union(x*n+y+1, x*n+y);
                }
                if(y-1>=0 && mat[x][y-1] == 1){
                    myUf.Union(x*n+y-1, x*n+y);
                }
                if(x==0){ // merge to roof node
                    myUf.Union(m*n, x*n+y);
                }
                int curRoofRank = myUf.GetRank(m*n);

                int curPar = myUf.Find(x*n+y);
                int roofPar = myUf.Find(m*n);
                if(curPar == roofPar){
                    res.push_back(curRoofRank- prevRoofRank -1);
                }
                else{
                    res.push_back(curRoofRank- prevRoofRank);
                }

            }
            else{
                res.push_back(0);
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};


//DFS (surprisingly faster)
class Solution {
public:
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    
    int connect(vector<vector<int>>& grid, int x, int y) {
        int n = grid.size(), m = grid[0].size();
        if (x >= n || y >= m || x < 0 || y < 0 || grid[x][y] != 1) {
            return 0;
        }
        
        int ans = 1;
        grid[x][y] = 2;
        for (int i = 0; i < 4; ++i) {
            ans += connect(grid, x + dx[i], y + dy[i]);
        }
        return ans;
    }
    
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int n = grid.size(), m = grid[0].size();
        int h = hits.size();
        vector<int> ret;
        ret.resize(h);
        for (int i = 0; i < h; ++i) {
            grid[hits[i][0]][hits[i][1]] *= -1;
        }
        for (int i = 0; i < m; ++i) {
            connect(grid, 0, i);
        }
        for (int i = h - 1; i >= 0; --i) {
            int xx = hits[i][0], yy = hits[i][1];
            if (grid[xx][yy] != -1) {
                continue;
            }
            grid[xx][yy] = 1;
            for (int j = 0; j < 4; ++j) {
                int x = xx + dx[j], y = yy + dy[j];
                if ((x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 2) || xx == 0) {
                    grid[xx][yy] = 2;
                    //cout << "xx = " << xx << " yy = " << yy << " x = " << x << " y = "<< y << " " << i << " "<< j << endl;
                    for (int k = 0; k < 4; ++k) {
                        ret[i] += connect(grid, xx + dx[k], yy + dy[k]);
                    }
                    break;
                }
            }
        }
        return ret;
    }
};
