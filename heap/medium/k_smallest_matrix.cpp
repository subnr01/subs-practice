/*
Given a n x n matrix where each of the rows and columns are sorted in ascending order,
find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
Note: 
You may assume k is always valid, 1 ≤ k ≤ n2.

*/


//my soln
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        priority_queue<int, vector<int>, greater<int>> pq;
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++) {
                pq.push(matrix[i][j]);    
            }
            
        }
        
        int i = 0;
        while(i < k - 1)
        {
            pq.pop();
            i++;
            
        }
        
        return pq.top();
        
    }
};

//binary search
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
    
 // using heap
 class Solution {
public:
struct compare
{
    bool operator()(const pair<int,pair<int, int> >& a, const pair<int,pair<int, int> >& b)
    {
        return a.first>b.first;
    }
};
    int kthSmallest(vector<vector<int>>& arr, int k) {
        
        int n=arr.size(),m=arr[0].size();
        
        priority_queue< pair<int,pair<int, int> >, vector<pair<int, pair<int, int> > >, compare > p;
        
        for(int i=0;i<n;i++)
        p.push(make_pair(arr[i][0],make_pair(i,0)));
        
        int x=k,ans;
        while(x--)
        {
            int e=p.top().first;
            int i=p.top().second.first;
            int j=p.top().second.second;
            ans=e;
            p.pop();
            if(j!=m-1)
            p.push(make_pair(arr[i][j+1],make_pair(i,j+1)));
        }
        return ans;
        
    }
};
