/*

You are given an integer array sorted in ascending order (may contain duplicates),
you need to split them into several subsequences, where each subsequences consist of 
at least 3 consecutive integers. Return whether you can make such a split.

Example 1:
Input: [1,2,3,3,4,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3
3, 4, 5
Example 2:
Input: [1,2,3,3,4,4,5,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3, 4, 5
3, 4, 5
Example 3:
Input: [1,2,3,4,4,5]
Output: False
Note:
The length of the input is in range of [1, 10000]

*/

//Is this O(nlogn) or O(n)
class Solution {
public:
	bool isPossible(vector<int>& nums)
	{
		unordered_map<int, priority_queue<int, vector<int>, std::greater<int>>> backs;

		// Keep track of the number of sequences with size < 3
		int need_more = 0;

		for (int num : nums)
		{
			if (! backs[num - 1].empty())
			{	// There exists a sequence that ends in num-1
				// Append 'num' to this sequence
				// Remove the existing sequence
				// Add a new sequence ending in 'num' with size incremented by 1 
				int count = backs[num - 1].top();
				backs[num - 1].pop();
				backs[num].push(++count);

				if (count == 3)
					need_more--;
			}
			else
			{	// There is no sequence that ends in num-1
				// Create a new sequence with size 1 that ends with 'num'
				backs[num].push(1);
				need_more++;
			}
		}
		return need_more == 0;
	}
};


//O(n) solution using DP???

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        int n = nums.size(), k = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i]-nums[i-1] > 1) {
                if (!check(nums, k, i)) 
                    return false;
                k = i;
            }
        }
        return check(nums, k, n);
    }
private:
    bool check(vector<int>& nums, int s, int e) {
        int ones = 0, twos = 0, tot = 0;
        for (int i = s+1, cnt = 1; i <= e; i++) {
            if (i < e && nums[i] == nums[i-1])
                cnt++;
            else {
                if (cnt < ones + twos) return false;
                twos = ones;
                ones = max(0, cnt-tot);
                tot = cnt;
                cnt = 1;
            }
        }
        return ones == 0 && twos == 0;
    }
};
