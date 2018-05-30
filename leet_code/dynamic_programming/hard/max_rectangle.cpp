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
        vector<int> temp(matrix[0].size(), 0);
        size_t sz = matrix[0].size();
        
        for(int i = 0; i < matrix.size(); ++i) {
            for(int j = 0; j < sz; ++j) {
                if(matrix[i][j] == '0') {
                    temp[j] = 0;
                } else {
                    temp[j]++;
                }
            }
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


//88%
class Solution {
public:
int maximalRectangle(vector<vector<char> > &mat) {
    int max_A = 0,  nrow = mat.size();
    if(nrow==0) return 0;
    int ncol = mat[0].size();
    int left[ncol], right[ncol], height[ncol]; // left[j] mean the left border of the j col
    for(int i=0; i<ncol; left[i] = -1, right[i] = ncol, height[i] = 0, i++);
    
    //start dp
    for(int i=0; i<nrow; i++){
        vector<char> cur_row = mat[i];
        int cur_left = -1, cur_right = ncol;  // ***** this is very important to do max(left[j], cur_left);
        //for each row to update the left[j] and right[j] and height[j]
        for(int j=0; j<ncol; j++){
            if(cur_row[j] == '1'){
                left[j] = max(left[j], cur_left);   height[j] += 1;
            }
            else{
                left[j] = -1; // *** this step is necessary to do max(left[j], cur_left); don't worry it because the height[j] =0 to make area =0;
                cur_left = j;   height[j] = 0;
            }
        }
        // update the right[j]
        for(int j=ncol-1; j>=0; j--){
            if(cur_row[j]=='1'){
                right[j] = min(right[j], cur_right);
            }
            else{
                right[j]  = ncol; //*** this step is necessary to do min(right[j], cur_right);  don't worry it because the height[j] =0 to make area =0;
                cur_right = j;
            }
        }
        
        // update max_A
        for(int j=0; j<ncol; j++){
            //cout<<"right["<<j<<"], left["<<j<<"],  height["<<j<<"] = "<<right[j]<<","<<left[j]<<","<<height[j]<<endl;
            max_A = max(max_A, (right[j] - left[j] - 1) * height[j]);
            //cout << " max_A = "<<max_A<<endl;
        }
    }
    return max_A;
}
};
