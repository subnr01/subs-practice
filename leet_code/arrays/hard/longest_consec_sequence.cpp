/*

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

Example:

Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

*/


//Related topics: array, union find




//very fast solution O(n)
class Solution {
public:
    //可以把问题拆解为以nums[i]为起点的有序序列，如果有比nums[i]小的，则直接跳过
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> dict(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            if (dict.count(x - 1)) continue;
            int y = x + 1;
            while (dict.count(y)) {
                ++y;
            }
            
            if (y - x > ans) {
                ans = y - x;
            }
        }
        return ans;
    }
};


//using sort, easier and interesting and intuitive.
//Time complexity: O (nlogn)
//Space complexity: O(1) because we sort the array in place.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) 
    {
        if (nums.size() == 0)
        {
            return 0;
        }
        int longst = 1;
        int currst = 1;
        
        sort (nums.begin(), nums.end());
        
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] != nums[i-1]) {
                if (nums[i] == nums[i-1] + 1)
                {
                    currst++;
                } else {
                    longst = max(longst, currst);
                    currst = 1;
                }
            }
            
        }
        //For inputs like (0, -1) where longst is
        // not updated, we need the max in
        // the return statement.
        return max(longst, currst);
    }
};
