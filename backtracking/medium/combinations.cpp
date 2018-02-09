/*
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

*/

//Check out the iterative solutions

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        
        vector<vector<int>> res;
        if (k > n)
        {
            return res;
        }
        
        vector<int> cand;
        comb(res, cand, 0, 0, n, k);
        return res;
        
    }
    
    
    void comb(vector<vector<int>>& res, vector<int> &cand, int start, int num, int n, int k)
    {
        //if num is equal to k
        if (num == k)
        {
            res.push_back(cand);
            return;
        }
        
        for (int i = start; i < n; i++)
        {
            //WATCH THE i+1 here, unlike the other backtracking solutions.
            cand.push_back(i+1);
            comb(res, cand, i + 1, num + 1, n, k);
            cand.pop_back();
        }
        return;
    }
};
