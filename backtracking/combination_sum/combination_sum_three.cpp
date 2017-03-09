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
    std::vector<std::vector<int> > combinationSum3(int k, int n) {
        std::vector<std::vector<int> > res;
        std::vector<int> combination;
        combinationSum3(n, res, combination, 1, k);
        return res;
    }
private:
    void combinationSum3(int target, std::vector<std::vector<int> > &res, std::vector<int> &combination, int begin, int need) {
		if (!target) {
			res.push_back(combination);
			return;
		}
		else if (!need)
			return;
        for (int i = begin; i != 10 && target; ++i) {
            int max = i * need + need * (need - 1) / 2;
            if (target< max) {
                return;
            }
			combination.push_back(i);
			combinationSum3(target - i, res, combination, i + 1, need - 1);
			combination.pop_back();
        }
    }
};
