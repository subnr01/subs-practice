/*

Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.
Write a function that takes an integer n and return all possible combinations of its factors.

Examples:
input: 1
output: 
[]
input: 37
output: 
[]
input: 12
output:
[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]
input: 32
output:
[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]

*/

class Solution {
private:
    vector<vector<int>> res;
public:
    vector<vector<int>> getFactors(int n) {
        vector<int> line;
        getFHelp(n, 2, line);
        return res;
    }
    
    void getFHelp(int n, int bottom, vector<int> line) {
        for(int i=bottom; i<=sqrt(n); i++){
            if(n%i == 0) {
                vector<int> new_line = line;
                new_line.push_back(i);
                getFHelp(n/i, i, new_line);
                new_line.push_back(n/i);
                res.push_back(new_line);
            }
        }
    }
};


//not using sqrt
class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> res;
        
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                vector<int> tmp = {i, n / i};
                res.push_back(tmp);
                helper(tmp, res);
            }
        }
        
        return res;
    }
    
    void helper(vector<int>& cur, vector<vector<int>>& res) {
        int back = cur.back();
        cur.pop_back();
        
        for (int i = 2; i * i <= back; ++i) {
            if (back % i == 0 && i >= cur.back()) {
                cur.push_back(i);
                cur.push_back(back / i);
                res.push_back(cur);
                helper(cur, res);
                cur.pop_back();
                cur.pop_back();
            }
        }
        
        cur.push_back(back);
    }
};
