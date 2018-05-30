/*

Given a sorted positive integer array nums and an integer n, add/patch elements to the array such
that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. 
Return the minimum number of patches required.

Example 1:

Input: nums = [1,3], n = 6
Output: 1 
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
Example 2:

Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
Example 3:

Input: nums = [1,2,2], n = 5
Output: 0
*/

//wihtout sorting
class Solution {
public:
int minPatches(vector<int>& nums, int n) {
        int i=0, count=0; 
        long curr = 1;
        while (curr <= n) {
            if (i>= nums.size() || nums[i] > curr) { // 2)
                count++; // add curr to nums
                curr += curr; 
            }
            else { // 1)
                curr = curr + nums[i];
                i++;
            }
        }
        return count;
    }
};


//With sorting
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        sort(nums.begin(), nums.end());
        int m = nums.size();
        long long now = 0;
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            while (now + 1 < nums[i]) {
                now = now * 2 + 1;
                ++ans;
                if (now >= n) break;
            }
            now += nums[i];
            if (now >= n) break;
        }
        while (now < n) {
            now = now * 2 + 1;
            ++ans;
        }
        return ans;
    }
};

    
