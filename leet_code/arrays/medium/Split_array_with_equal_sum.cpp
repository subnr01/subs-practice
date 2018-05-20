/*
Split Array with Equal Sum 

Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:

0 < i, i + 1 < j, j + 1 < k < n - 1
Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
where we define that subarray (L, R) represents a slice of the original array starting from the element indexed 
L to the element indexed R.

Example:

Input: [1,2,1,2,1,2,1]
Output: True
Explanation:
i = 1, j = 3, k = 5. 
sum(0, i - 1) = sum(0, 0) = 1
sum(i + 1, j - 1) = sum(2, 2) = 1
sum(j + 1, k - 1) = sum(4, 4) = 1
sum(k + 1, n - 1) = sum(6, 6) = 1


*/


/*
Time complexity : O(n^2)
One outer loop and two inner loops are used.

Space complexity : O(n)O(n). HashSet size can go upto nn.

*/


//TOO AMBIGIOUS, REFER GEEKS and GEEKS

class Solution {
public:
    bool splitArray(vector<int>& nums) {
        vector<int> sum;
        int prev = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0 && i > 0 && nums[i - 1] == 0)  continue; // skip extra 0s to accelerate
            prev += nums[i];
            sum.push_back(prev);
        }

        int n = sum.size();
        for (int j = 3; j < n - 3; j++) {
            set<int> subsums;
            for (int i = 1; i < j - 1; i++) {
        
                if (sum[i - 1] == sum[j - 1] - sum[i]) {
                    subsums.insert(sum[i - 1]);
                }
            }

            for (int k = j + 1; k < n - 1; k++) {
                int sum1 = sum[k - 1] - sum[j];
                int sum2 = sum[n - 1] - sum[k];
                if (sum1 == sum2 && subsums.count(sum1)) {
                    return true;
                }
            }
        }

        return false;
    }
};
