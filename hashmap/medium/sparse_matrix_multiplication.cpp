
/*

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]


     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |


*/




//With hash table
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
      if ( A.empty() || B.empty() ) return vector<vector<int>>();
      vector< pair< pair<int, int>, int > > mapA, mapB;
      int n = A.size(), m = A[0].size(), p = B[0].size();
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          if ( A[i][j] != 0 )
            mapA.push_back( { {i, j}, A[i][j] } );
        }
      }
      for (int k = 0; k < p; k++) {
        for (int j = 0; j < m; j++) {
          if ( B[j][k] != 0 )
            mapB.push_back( { {j, k}, B[j][k] } );
        }
      }
      vector<vector<int>> res(n, vector<int>(p, 0));
      for (auto ha: mapA) {
        for (auto hb: mapB) {
          if (ha.first.second == hb.first.first)
            res[ha.first.first][hb.first.second] += ha.second * hb.second;
        }
      }
      return res;
    }
};








//Without hash table
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        
        int m = A.size(), nA = A[0].size(), n = B[0].size();
        vector<vector<int>> res(m, vector<int>(n, 0));
        
        for (int i=0; i<m; ++i) {
            for (int j=0; j<nA; ++j) {
                if (A[i][j] != 0) {
                    for (int k=0; k<n; ++k) {
                        if (B[j][k] != 0) {
                            res[i][k] += A[i][j] * B[j][k];
                        }
                    }
                }
            }
        }
        return res;
    }
};
