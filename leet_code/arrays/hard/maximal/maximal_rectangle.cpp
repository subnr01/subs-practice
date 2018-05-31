/*
Given a 2D binary matrix filled with 0's and 1's, find the largest 
rectangle containing only 1's and return its area.
For example, given the following matrix:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.
*/

//Related topics: array, hash, DP

//34%
class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
         if(matrix.empty()){
            return 0;
         }
        int max_area = 0;
        //We are taking a matrix with the size of columns
        
        vector<int> temp(matrix[0].size(), 0);
        size_t sz = matrix[0].size();
        
        for(int i = 0; i < matrix.size(); ++i) {
            for(int j = 0; j < sz; ++j) {
                // the temp [j] will contain the number
                // of 1s encountered without zeros in each
                // column.
                if(matrix[i][j] == '0') {
                    temp[j] = 0;
                } else {
                    temp[j]++;
                }
            }
            // find the area for each row using the values of temp[j].
            // the final row with have the cumulative number of 1s, 
            // representing height of a perfect histogram.
            max_area = max(max_area,largestRectangleArea(temp));
        }
        return max_area;
    }
    
    
    //brute force, O(n^2)
    int largestRectangleArea(vector<int> &height) {
        height.push_back(0);
        size_t n = height.size();
        
        int max_area = 0;
        int i = 0;
        stack<int> mystack;
        
        while(i < n) {
            if(mystack.empty() || height[i] >= height[mystack.top()]) {
                mystack.push(i);
                i++;
            } else {
                int h = height[mystack.top()];
                mystack.pop();
                int w = mystack.empty()? i: i - mystack.top() - 1;
                max_area = max(max_area, h * w);
            }
            
            
        }
        return max_area;
    }
    
};
