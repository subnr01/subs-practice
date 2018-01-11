/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.
For example, given the following matrix:
1101
1101
1111
Return 4.
*/

//Brute force
class Solution {
public:
int maximalSquare(vector<vector<char>>& matrix) {
    /*
    if (matrix.size() == 0) {
        return 0;
    }*/
    int rows = matrix.size();
    //int cols = matrix[0].size();
    int cols = rows;
    int sqlen = 0;
    int maxlen = 0;
    bool flag = false;
    
    for( int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j) {
            if(matrix[i][j] == '1') {
                sqlen = 1;
                flag = true;
                while(i + sqlen < rows && j + sqlen < cols && flag) {
                    for(int k = j; k <= j + sqlen; k++) {
                        if(matrix[i+sqlen][k] == '0') {
                            flag = false;
                            break;
                        }
                    }
                    for(int k = i; k <= i + sqlen; k++) {
                        if(matrix[k][j+sqlen] == '0') {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        sqlen++;
                    }
                    
                    
                }
                
            }
            maxlen = max(maxlen, sqlen);
        }
        
    }   
    return maxlen * maxlen;
}

};

//For explanation read https://leetcode.com/problems/maximal-square/discuss/61803
/*
First, it is obvious that for the topmost row (i = 0) and the leftmost column (j = 0), 
P[i][j] = matrix[i][j]. This is easily understood. Let’s suppose that the topmost row of
matrix is like [1, 0, 0, 1]. Then we can immediately know that the first and last point can be a
square of size 1 while the two middle points cannot make any square, giving a size of 0. 
Thus, P = [1, 0, 0, 1], which is the same as matrix. The case is similar for the leftmost column. 
Till now, the boundary conditions of this DP problem are solved.
Let’s move to the more general case for P[i][j] in which i > 0 and j > 0. First of all, 
let’s see another simple case in which matrix[i][j] = 0. It is obvious that P[i][j] = 0 too. 
Why? Well, since matrix[i][j] = 0, no square will contain matrix[i][j]. According to our 
definition of P[i][j], P[i][j] is also 0.
Now we are almost done. The only unsolved case is matrix[i][j] = 1. Let’s see an example.
Suppose matrix = [[0, 1], [1, 1]], it is obvious that P[0][0] = 0, P[0][1] = P[1][0] = 1, what 
about P[1][1]? Well, to give a square of size larger than 1 in P[1][1], all of its 
three neighbors (left, up, left-up) should be non-zero, right? In this case, the
left-up neighbor P[0][0] = 0, so P[1][1] can only be 1, which means that it contains the square of itself.
*/

//Dynamic programming using a 2D array
int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if (!m) return 0;
    int n = matrix[0].size();
    vector<vector<int> > size(m, vector<int>(n, 0));
    int maxsize = 0;
    for (int j = 0; j < n; j++) {
        size[0][j] = matrix[0][j] - '0';
        maxsize = max(maxsize, size[0][j]);
    }
    for (int i = 1; i < m; i++) {
        size[i][0] = matrix[i][0] - '0';
        maxsize = max(maxsize, size[i][0]);
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == '1') {
                size[i][j] = min(size[i - 1][j - 1], min(size[i - 1][j], size[i][j - 1])) + 1;
                maxsize = max(maxsize, size[i][j]);
            }
        }
    }
    return maxsize * maxsize;
}

//Dynamic programming using a 1D array
class Solution {
public:
int maximalSquare(vector<vector<char>>& matrix) {
    int nr = matrix.size(); if (nr == 0) return 0;
    int nc = matrix[0].size(); if (nc == 0) return 0;
    
    vector<int> dp(nc+1, 0);
    
    int maxsize = 0;
    
    int last_topleft = 0;  // This is 'pre[i-1]' for the current element
    
    for (int ir = 1; ir <= nr; ++ir) {
        for (int ic = 1; ic <= nc; ++ic) {
            int temp = dp[ic];      // This is 'pre[i-1]' for the next element                
             if (matrix[ir-1][ic-1] == '0') dp[ic] = 0; 
            else {
                dp[ic] = min(min(dp[ic], dp[ic-1]), last_topleft) + 1;
                maxsize = max(maxsize, dp[ic]);
            }
            last_topleft = temp;  // update 'pre[i-1]'
        }
    }
    return maxsize * maxsize;
}
};
