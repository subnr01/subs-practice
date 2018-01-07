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
    vector<vector<int>> combinationSum3(int k, int n) { 
		std::vector<std::vector<int> > res;
        std::vector<int> combination;
        int start = 1;
        combinationSum2(n, res, combination, k, start);
        return res;
    }
private:
    void combinationSum2(int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int k, int begin) 
    {
	if  (combination.size() == k) {
		if (!target) {
                   res.push_back(combination);
        	}
		return;
	} 
        
	for (int i = begin; i < 10 && target >= i; ++i) {
            combination.push_back(i);
            combinationSum2(target - i, res, combination, k, i + 1);
            combination.pop_back();
            
        }
    }
};
