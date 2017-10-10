/*
Given a 2-d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded
by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges 
of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

*/


//DFS solution where O(m*n)

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) 
        {
            return 0;
        }
        int count = 0;
        vector<vector<char>> test;
        
        //Note how two vectors are copied here
        // No need to use a for loop like arrays
        // the assignment operator takes care
        // of copying the elements between two
        // vectors
        test = grid;
        
        int row = test.size();
        int col = test[0].size();
        
        for (int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if (test[i][j] == '1') {
                    count++;
                    merge(test, i, j);
                }
            }
        }
        return count;
        
    }
    
    
    void merge(vector<vector<char>>&test, int i, int j)
    {
        if(i == test.size() || j == test[0].size() || i < 0 || j < 0 || test[i][j] == '0') {
            return;
        }
        //recursively update all neighboring '1's 
        // until a zero is found when you return
        test[i][j] = '0';
        merge(test, i+1, j);
        merge(test, i, j+1);
        merge(test, i-1, j);
        merge(test, i, j-1);
    }
    
};


//Using union find
public int numIslands(char[][] grid) {
    if(grid==null || grid.length==0||grid[0].length==0)
        return 0;
 
    int m = grid.length;
    int n = grid[0].length;
 
    int count=0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='1'){
                count++;
                merge(grid, i, j);
            }
        }
    }
 
    return count;
}
 
public void merge(char[][] grid, int i, int j){
    int m=grid.length;
    int n=grid[0].length;
 
    if(i<0||i>=m||j<0||j>=n||grid[i][j]!='1')
        return;
 
    grid[i][j]='X';
 
    merge(grid, i-1, j);
    merge(grid, i+1, j);
    merge(grid, i, j-1);
    merge(grid, i, j+1);
}
Java Solution 2 - Union-Find

Time is O(m*n*log(k)).

public int numIslands(char[][] grid) {
    if(grid==null || grid.length==0 || grid[0].length==0)
        return 0;
 
    int m = grid.length;
    int n = grid[0].length;
 
    int[] dx={-1, 1, 0, 0};
    int[] dy={0, 0, -1, 1};
 
    int[] root = new int[m*n];
 
    int count=0;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='1'){
                root[i*n+j] = i*n+j;            
                count++;
            }
        }
    }
 
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]=='1'){
                for(int k=0; k<4; k++){
                    int x = i+dx[k];
                    int y = j+dy[k];
 
                    if(x>=0&&x<m&&y>=0&&y<n&&grid[x][y]=='1'){
                        int cRoot = getRoot(root, i*n+j);
                        int nRoot = getRoot(root, x*n+y);
                        if(nRoot!=cRoot){
                            root[cRoot]=nRoot; //update previous node's root to be current
                            count--;
                        }
 
                    }
                }
            }
        }
    }
 
    return count;
}
 
public int getRoot(int[] arr , int i){
    while(arr[i]!=i){
        i = arr[arr[i]];
    }
 
    return i;
}


