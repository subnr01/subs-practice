/*
Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the
"Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.
Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.
Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.
Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:
Given the following 5x5 matrix:
  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic
Return:
[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
*/


//dfs soln
class Solution {
    int m, n;
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> ans;
        m = matrix.size();
        if(m == 0)
            return ans;
        n = matrix[0].size();
        vector<vector<int>> v(m, vector<int>(n, 0));
        for(int i=0; i<m; i++){
            dfs(i, 0, 1, v, matrix);
            dfs(i, n-1, 2, v, matrix);
        }
            
        for(int j=0; j<n; j++){
            dfs(0, j, 1, v, matrix);
            dfs(m-1, j, 2, v, matrix);
        }
        
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                if(v[i][j] == 3){
                    ans.push_back({i, j});
                }
        return ans;
    }
    
    void dfs(int i, int j, int col, vector<vector<int>>& v, vector<vector<int>>& matrix){
        if(v[i][j] & col)
            return;
        v[i][j] |= col;
        if(i > 0 && matrix[i-1][j] >= matrix[i][j])
            dfs(i-1, j, col, v, matrix);
        if(i < m-1 && matrix[i+1][j] >= matrix[i][j])
            dfs(i+1, j, col, v, matrix);
        if(j>0 && matrix[i][j-1] >= matrix[i][j])
            dfs(i, j-1, col, v, matrix);
        if(j < n-1 && matrix[i][j+1] >= matrix[i][j])
            dfs(i, j+1, col, v, matrix);
    }
};


//Easy soln
class Solution {
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int,int>> result;
        int m=matrix.size();
        if (m==0) return result;
        int n=matrix[0].size();
        int pacific[m][n];
        int atlantic[m][n];
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                pacific[i][j]=0;
                atlantic[i][j]=0;
            }
        }
        stack<pair<int,int>> sp;
        stack<pair<int,int>> sa;
        for (int i=0;i<m;i++){
            pacific[i][0]=1;
            sp.push(make_pair(i,0));
        }
        for(int i=1;i<n;i++){
            pacific[0][i]=1;
            sp.push(make_pair(0,i));
        }
        while(!sp.empty()){
            pair<int, int> index=sp.top();
            int x=index.first;
            int y=index.second;
            sp.pop();
            if (x-1>=0&&pacific[x-1][y]==0&&matrix[x-1][y]>=matrix[x][y]){
                sp.push(make_pair(x-1,y));
                pacific[x-1][y]=1;
            }
            if (x+1<m&&pacific[x+1][y]==0&&matrix[x+1][y]>=matrix[x][y]){
                sp.push(make_pair(x+1,y));
                pacific[x+1][y]=1;
            }
            if (y-1>=0&&pacific[x][y-1]==0&&matrix[x][y-1]>=matrix[x][y]){
                sp.push(make_pair(x,y-1));
                pacific[x][y-1]=1;
            }
            if (y+1<n&&pacific[x][y+1]==0&&matrix[x][y+1]>=matrix[x][y]){
                sp.push(make_pair(x,y+1));
                pacific[x][y+1]=1;
            }
        }
        for (int i=0;i<m;i++){
            atlantic[i][n-1]=1;
            sa.push(make_pair(i,n-1));
        }
        for(int i=0;i<n-1;i++){
            atlantic[m-1][i]=1;
            sa.push(make_pair(m-1,i));
        }
        while(!sa.empty()){
            pair<int, int> index=sa.top();
            int x=index.first;
            int y=index.second;
            sa.pop();
            if (x-1>=0&&atlantic[x-1][y]==0&&matrix[x-1][y]>=matrix[x][y]){
                sa.push(make_pair(x-1,y));
                atlantic[x-1][y]=1;
            }
            if (x+1<m&&atlantic[x+1][y]==0&&matrix[x+1][y]>=matrix[x][y]){
                sa.push(make_pair(x+1,y));
                atlantic[x+1][y]=1;
            }
            if (y-1>=0&&atlantic[x][y-1]==0&&matrix[x][y-1]>=matrix[x][y]){
                sa.push(make_pair(x,y-1));
                atlantic[x][y-1]=1;
            }
            if (y+1<n&&atlantic[x][y+1]==0&&matrix[x][y+1]>=matrix[x][y]){
                sa.push(make_pair(x,y+1));
                atlantic[x][y+1]=1;
            }
        }
        for(int i=0; i<m;i++){
            for(int j=0;j<n;j++){
                if (atlantic[i][j]==1&&pacific[i][j]==1){
                    result.push_back(make_pair(i,j));
                }
            }
        }
        return result;
    }
};
