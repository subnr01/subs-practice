/*

Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the
candidate numbers sums to T. The same repeated number may be chosen from C unlimited number of times.

Note: All numbers (including target) will be positive integers. Elements in a combination (a1, a2, ... , ak) must be
in non-descending order. (ie, a1 <= a2 <= ... <= ak). The solution set must not contain duplicate combinations.
For example, given candidate set 2,3,6,7 and target 7, A solution set is:

[7] 
[2, 2, 3]
*/

//DFS approach

class Solution {
public:
    std::vector<std::vector<int> > combinationSum(std::vector<int> &candidates, int target) {
		std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int> > res;
        std::vector<int> combination;
        combinationSum(candidates, target, res, combination, 0);
        return res;
    }
private:
    void combinationSum(std::vector<int> &candidates, int target, std::vector<std::vector<int> > &res, 
			std::vector<int> &combination, int begin) {
		if  (!target) {
			res.push_back(combination);
			return;
		}
        for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
            combination.push_back(candidates[i]);
            combinationSum(candidates, target - candidates[i], res, combination, i);
            combination.pop_back();
        }
    }
};
