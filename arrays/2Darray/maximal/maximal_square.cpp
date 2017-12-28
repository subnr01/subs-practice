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





