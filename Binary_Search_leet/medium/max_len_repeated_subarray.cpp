/*

Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:
Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation: 
The repeated subarray with maximum length is [3, 2, 1].

*/

//Related topics:
//DP and binarysearch


//DP formula
/**
 * dp[i][j] = a[i] == b[j] ? dp[i + 1][j + 1] : 0;
 * dp[i][j] : max lenth of common subarray start at a[i] & b[j];
 */
 
 //Time complexity: m * n 
 // space complexity: m * n

class Solution {
public:
    int findLength(vector<int>& a, vector<int>& b) {
        int m = a.size(), n = b.size();
        if (!m || !n) return 0;
        vector<int> dp(n + 1);
        int res = 0;
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                res = max(res, dp[j] = a[i] == b[j] ? 1 + dp[j + 1] : 0);
            }
        }
        return res;
    }
};


//Binary search soln not good

//Java
class Solution {
    public boolean check(int length, int[] A, int[] B) {
        Set<String> seen = new HashSet();
        for (int i = 0; i + length <= A.length; ++i) {
            seen.add(Arrays.toString(Arrays.copyOfRange(A, i, i+length)));
        }
        for (int j = 0; j + length <= B.length; ++j) {
            if (seen.contains(Arrays.toString(Arrays.copyOfRange(B, j, j+length)))) {
                return true;
            }
        }
        return false;
    }

    public int findLength(int[] A, int[] B) {
        int lo = 0, hi = Math.min(A.length, B.length) + 1;
        while (lo < hi) {
            int mi = (lo + hi) / 2;
            if (check(mi, A, B)) lo = mi + 1;
            else hi = mi;
        }
        return lo - 1;
    }
}

