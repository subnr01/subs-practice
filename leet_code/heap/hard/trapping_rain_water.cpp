/* 
trapping rain water
*/


//https://leetcode.com/problems/trapping-rain-water-ii/description/



class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.size()==0) return 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
        int row = heightMap.size(), col = heightMap[0].size();
        vector<vector<int>> visited(row, vector<int>(col, 0));
        int ans = 0, Max = INT_MIN;
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if(!(i==0 || i==row-1 || j==0 || j==col-1)) continue;
                que.push(make_pair(heightMap[i][j], i*col+j));
                visited[i][j] = 1;
            }
        }
        vector<vector<int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while(!que.empty())
        {
            auto val = que.top(); que.pop();
            int height = val.first, x = val.second/col, y = val.second%col;
            Max = max(Max, height);
            for(auto d: dir)
            {
                int x2 = x + d[0], y2 = y + d[1];
                if(x2>=row || x2<0 || y2<0 || y2>=col || visited[x2][y2]) continue;
                visited[x2][y2] = 1;
                if(heightMap[x2][y2] < Max) ans += Max - heightMap[x2][y2];
                que.push(make_pair(heightMap[x2][y2], x2*col+y2));
            }
        }
        return ans;
    }
};

//very fasst soln
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.empty() || heightMap[0].empty()) return 0;
        const int m = heightMap.size(), n=heightMap[0].size();
        priority_queue<Cell> pq;
        vector<vector<bool>> visited(m,vector<bool>(n,false));
        for(int j=0; j<n; j++) {
            pq.push(Cell(0,j,heightMap[0][j]));
            pq.push(Cell(m-1,j,heightMap[m-1][j]));
            visited[0][j]=true;
            visited[m-1][j]=true;
        }
        for(int i=1; i<m-1; i++) {
            pq.push(Cell(i,0,heightMap[i][0]));
            pq.push(Cell(i,n-1,heightMap[i][n-1]));
            visited[i][0]=true;
            visited[i][n-1]=true;
        }
        vector<int> xi({1,-1,0,0}), yi({0,0,1,-1});
        int water=0;
        while(!pq.empty()) {
            Cell cc = pq.top();
            pq.pop();
            for(int i=0; i<4; i++) {
                int xx=cc.x+xi[i], yy=cc.y+yi[i];
                if(xx<0 || xx>=m || yy<0 || yy>=n || visited[xx][yy]) continue;
                visited[xx][yy]=true;
                water+=max(0,cc.h-heightMap[xx][yy]);
                pq.push(Cell(xx,yy,max(cc.h,heightMap[xx][yy])));
            }
        }
        return water;
    }
    
private:
    struct Cell {
        Cell(int xx, int yy, int hh):x(xx), y(yy), h(hh) {}
        bool operator<(const Cell& rhs) const{
            return this->h > rhs.h;
        }
        int x, y, h;
    };
};
