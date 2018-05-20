/*
Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, 
excluding [11,22,33,44,55,66,77,88,99])



*/

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int sum = 1;
        for (int i=1; i<=n; ++i) {
            sum += helper(i);
        }
        return sum;
    }
    int helper(int n) {
        if (n > 10) return 0;
        int res = 9, factor = 9;
        for (int i=2; i<=n; ++i) {
            res *= factor;
            factor--;
        }
        return res;
    }
};
