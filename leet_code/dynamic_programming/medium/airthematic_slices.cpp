/*

A sequence of number is called arithmetic if it consists of at least three elements and 
if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

Example:

A = [1, 2, 3, 4]

return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
*/


class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        vector<int> dp(n + 1);
        int sum = 0;
        for (int i = 2; i < n; i++)
        {
            if (A[i] - A[i-1] == A[i-1] - A[i - 2]){
                dp[i] = dp[i - 1] + 1;
                sum += dp[i];
            }
        }
        return sum;
        
    }
};
