/*

Given an integer array, your task is to find all the different possible increasing subsequences of the given array, and the length of an increasing subsequence should be at least 2 .

Example:
Input: [4, 6, 7, 7]
Output: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
Note:
The length of the given array will not exceed 15.
The range of integer in the given array is [-100,100].
The given array may contain duplicates, and two equal integers should also be considered as a special case of increasing sequence.
*/


https://discuss.leetcode.com/topic/76358/9-liner-beat-98-8-no-set-vector-hasher-or-helper-function-detailed-explanation


class Solution {
private:
    void findSubsequences(vector<int> &nums, vector<int> &subsequence,
                        set<vector<int> > &result, int size, int index) {
    if (size >= 2)
        result.insert(subsequence);


    for (int i = index; i < nums.size(); ++i) {
        if (subsequence.size() == 0 || nums[i] >= subsequence[subsequence.size() - 1]) {
            subsequence.push_back(nums[i]);
            findSubsequences(nums, subsequence, result, size + 1, i + 1);
            subsequence.pop_back();
        }
    }
}

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> resultSet;
        vector<int> subsequence;
        findSubsequences(nums, subsequence, resultSet, 0, 0);

        vector<vector<int>> result(resultSet.begin(), resultSet.end());
        return result;
    }
};
