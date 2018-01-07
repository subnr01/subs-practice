/*
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 
can be used and each combination should be a unique set of numbers.
Example 1:
Input: k = 3, n = 7
Output:
[[1,2,4]]
Example 2:
Input: k = 3, n = 9
Output:
[[1,2,6], [1,3,5], [2,3,4]]
*/

class Solution {
    
public:
    vector<vector<int>> combinationSum3(int k, int n)
    {
        vector<vector<int>> res;
        if (n == 0 || k == 0) {
            return res;
        }
        vector<int> arr;
        int start = 1;
        genSum(res, arr, start, k, n);
        return res;
    }
    
    void genSum(vector<vector<int>>& res, vector<int> &arr, int start, int k, int target)
    {
        if (arr.size() > k) {
            return;
        }
        if (arr.size() == k && target == 0)
        {
            res.push_back(arr);
            return;
        }
        
        for (int i = start; i < 10 && target >= i; i++) {
            arr.push_back(i);
            genSum(res, arr, i+1, k, target - i);
            arr.pop_back();
        }
        
    }
        
};

