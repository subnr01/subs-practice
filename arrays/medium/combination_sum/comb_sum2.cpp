/*

Given a collection of candidate numbers (C) and a target number (T), find all unique combinations
in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

*/


class Solution {
public:
    std::vector<std::vector<int> > combinationSum2(std::vector<int> &candidates, int target) {
		std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int> > res;
        std::vector<int> combination;
        combinationSum2(candidates, target, res, combination, 0);
        return res;
    }
private:
    void combinationSum2(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res,
			 std::vector<int> &combination, int begin) {
		if  (!target) {
			res.push_back(combination);
			return;
		}
		int i;
		
        for (i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
            /* 
	      we need the if condition here because we want to avoid duplicate solutions.
	      If we do not put this if condition, then we can get [1,2,5] repeated in the 
	      solution, beacuse of the second "1".
	     */
		
             /* 
		Also notice is set to begin, and begin is always (index+1), so
		(2,2,2,2) with target 8 will also give us the right solution.         
	     */		
			
            if (i != start && candidates[i] == candidates[i-1]) {
                continue;
            }
            arr.push_back(candidates[i]);
            genSum (candidates, res, i + 1, target - candidates[i], arr);
            arr.pop_back();
        }
    }
};
