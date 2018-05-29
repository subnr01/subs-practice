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

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        if (num.size() == 0) {
            return 0;
        }
        unordered_set<int> record(num.begin(),num.end());
        int res = 1;
        for(int n : num){
            if(record.find(n)==record.end()) continue;
            record.erase(n);
            int prev = n-1,next = n+1;
            while(record.find(prev)!=record.end()) record.erase(prev--);
            while(record.find(next)!=record.end()) record.erase(next++);
            res = max(res,next-prev-1);
        }
        return res;
    }
};


//Another similar soln (if you do not like erase)
//very fast solution
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
