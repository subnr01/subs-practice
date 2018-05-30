/*
Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle 
in the matrix such that its sum is no larger than k.

Example:
Given matrix = [
  [1,  0, 1],
  [0, -2, 3]
]
k = 2
The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2 is the max number no larger than k (k = 2).

*/


//related topics: binary search, DP, queue

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    if (matrix.empty()) return 0;
    int row = matrix.size(), col = matrix[0].size(), res = INT_MIN;
    for (int l = 0; l < col; ++l) {
        vector<int> sums(row, 0);
        for (int r = l; r < col; ++r) {
            for (int i = 0; i < row; ++i) {
                sums[i] += matrix[i][r];
            }
            
            // Find the max subarray no more than K 
            set<int> accuSet;
            accuSet.insert(0);
            int curSum = 0, curMax = INT_MIN;
            for (int sum : sums) {
                curSum += sum;
                set<int>::iterator it = accuSet.lower_bound(curSum - k);
                if (it != accuSet.end()) curMax = std::max(curMax, curSum - *it);
                accuSet.insert(curSum);
            }
            res = std::max(res, curMax);
        }
    }
    return res;
}
};

//another soln (98 %)
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m=matrix.size();
    if(m==0) return 0;
    int n=matrix[0].size();
    int res=INT_MIN;
    for(int i=0;i<n;i++) {  // the number of columns is smaller
        vector<int> sums(m,0);
        for(int j=i;j<n;j++) {
            for(int row=0;row<m;row++) {
                sums[row]+=matrix[row][j];
            }
            int ms = maxSumArray(sums, k);
            if (ms == k) return ms;
            if (ms < k && ms > res) res = ms;
      
        }
    }
    return res;
}
 
int maxSumArray(vector<int> & arr, int k) {
    int sum = 0, maxS = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {  //it's a trick. Maybe O(n) to solve this problem
        sum += arr[i];
        maxS = max(sum, maxS);
        if (sum == k ) return sum;
        if (sum < 0) sum = 0;
    }
    if (maxS <= k) return maxS;
    maxS= INT_MIN;
    set<int>sums;
    sum = 0;
    sums.insert(0);
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        auto it = sums.lower_bound(sum - k);
        if (it != sums.end()) maxS = max(sum - *it, maxS);
        sums.insert(sum);
    }
    return maxS;
}  
};
