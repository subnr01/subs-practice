/*
Remember the story of Little Match Girl? By now, you know exactly what matchsticks the 
little match girl has, please find out a way you can make one square by using up all those matchsticks.
You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

Your input will be several matchsticks the girl has, represented with their stick length. 
Your output will either be true or false, to represent whether you could make one square 
using all the matchsticks the little match girl has.

Example 1:
Input: [1,1,2,2,2]
Output: true

Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:
Input: [3,3,3,3,4]
Output: false

Explanation: You cannot find a way to form a square with all the matchsticks.


*/



class Solution {
private:
	bool findSum(const vector<int>& nums, int begin, int sum,
			vector<bool>& used) {
		if (sum == 0) {
			return true;
		}
		if (begin >= nums.size()) {
			return false;
		}

		for (int i = begin; i < nums.size(); i++) {
			if (used[i]) {
				continue;
			}

			if (nums[i] <= sum) {
				used[i] = true;
				if (findSum(nums, i + 1, sum - nums[i], used)) {
					return true;
				}
				used[i] = false;
			}
		}

		return false;
	}

public:
	bool makesquare(vector<int>& nums) {
		if (nums.size() < 4) {
			return false;
		}

		int sum = 0;
		for (int num : nums) {
			sum += num;
		}
		if (sum % 4 != 0) {
			return false;
		}

		sort(nums.begin(), nums.end(), greater<int>());
		vector<bool> used(nums.size(), false);
		int target = sum / 4;
		return findSum(nums, 0, target, used) && findSum(nums, 0, target, used)
				&& findSum(nums, 0, target, used);
	}
};
