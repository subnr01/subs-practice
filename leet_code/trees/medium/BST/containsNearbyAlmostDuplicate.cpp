/*
Given an array of integers, find out whether there are two distinct indices i
and j in the array such that the absolute difference between nums[i] and nums[j] is at most t 
and the absolute difference between i and j is at most k.

Example 1:

Input: nums = [1,2,3,1], k = 3, t = 0
Output: true
Example 2:

Input: nums = [1,0,1,1], k = 1, t = 2
Output: true
Example 3:

Input: nums = [1,5,9,1,5,9], k = 2, t = 3
Output: false


*/

/*
Solution

Need to understand this
// |x - nums[i]| <= t  ==> -t <= x - nums[i] <= t;
// x - nums[i] >= -t ==> x >= nums[i]-t 
// x - nums[i] <= t ==> |x - nums[i]| <= t    

So we try to find the lower_bound which is the first element equal or greater than.
If lower_bound exists and the difference between lower_bound and this element is
t, then we are good.

BTW, we maintain a sliding window of (k - 1) and erase the (i - k - 1) element from the set
in every iteration.

*/

class Solution {  
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        set<long> s;
        for (int i = 0; i < n; ++i) 
        {
            if (i > k) {
                s.erase(nums[i - k - 1]);
            }
            auto iter = s.lower_bound((long)nums[i] - (long)t);
            if (iter != s.end() && *iter - nums[i] <= t) {
                return true;
            }
            s.insert(nums[i]);
        }
        
        return false;
    }
};
