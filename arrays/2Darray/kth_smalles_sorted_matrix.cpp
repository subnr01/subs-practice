/*

Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element 
in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.

*/


class Solution
{
public:
	 int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        
        int left = matrix[0][0];
        int right = matrix[n-1][n-1];
        
        while (left < right) {
            int midv = (left + right) / 2;
            
            int count = 0;  // number of elements no bigger than midv
            for (int i = 0; i < n; i++) {
                vector<int>& row = matrix[i];
                count += std::upper_bound(row.begin(), row.end(), midv) - row.begin();
            }
            
            if (count < k) {
                left = midv + 1;
            } else {
                right = midv;    
            }
        }
        return left;
    }
};



//Another solution

class Solution {
public:
    struct cmp{
        bool operator() (const pair<int,pair<int,int>> &a, const pair<int,pair<int,int>> &b){
            return a.first > b.first;
        }
    };

    int kthSmallest(vector<vector<int>>& matrix, int k) {
        const int n = matrix.size();
        if(k == 1)  return matrix[0][0];

        priority_queue<pair<int,pair<int,int> >, vector <pair<int,pair<int,int>>  > , cmp> q;   // pair<matrix[i][j],pair<i,j>>
        for(int i = 0; i < n; i++){
            q.push({matrix[i][0],{i,0}});
        }
        int ans;
        
        for(int i = 0; i < k; i++){
            ans = q.top().first;
            int r = (q.top().second).first;
            int c = (q.top().second).second + 1;
            q.pop();
            if(c < n){  
                q.push({matrix[r][c],{r,c}});
            }
        }
        return ans;
    }
};



