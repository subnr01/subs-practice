/*

Refer leetcode

*/

//Related topics:  dynamic programming, bianry search

//http://leetcodesolution.blogspot.com/2015/01/leetcode-dungeon-game.html


//Sol 1
class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        int M = dungeon.size();
        int N = dungeon[0].size();
        // hp[i][j] represents the min hp needed at position (i, j)
        // Add dummy row and column at bottom and right side
        vector<vector<int> > hp(M + 1, vector<int>(N + 1, INT_MAX));
        hp[M][N - 1] = 1;
        hp[M - 1][N] = 1;
        for (int i = M - 1; i >= 0; i--) {
            for (int j = N - 1; j >= 0; j--) {
                int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
                hp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return hp[0][0];
    }
};


//ANother soln, maybe slightly slower
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size(), n = m==0? 0 : dungeon[0].size();
        vector<vector<int>> memo(m, vector<int>(n,0));
        for (int i=m-1; i>=0; --i) {
            for (int j=n-1; j>=0; --j) {
                int d = dungeon[i][j];
                if (i==m-1 && j==n-1) memo[i][j] = d>0? 0 : -d;
                else if (i==m-1) memo[i][j] = max(memo[i][j+1]-d, 0);
                else if (j==n-1) memo[i][j] = max(memo[i+1][j]-d, 0);
                else memo[i][j] = min(max(memo[i][j+1]-d, 0),max(memo[i+1][j]-d, 0));
            }
        }
        return memo[0][0]+1;
    }
};

