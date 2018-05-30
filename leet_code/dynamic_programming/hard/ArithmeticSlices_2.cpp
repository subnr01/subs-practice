/*
A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference
between any two consecutive elements is the same.

For example, these are arithmetic sequences:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.

1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A subsequence slice of that array 
is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0 < P1 < ... < Pk < N.

A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the 
sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this means that k ≥ 2.

The function should return the number of arithmetic subsequence slices in the array A.

The input contains N integers. Every integer is in the range of -231 and 231-1 
and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.


Example:

Input: [2, 4, 6, 8, 10]

Output: 7

Explanation:
All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]

*/


class Solution {
public:
int numberOfArithmeticSlices(vector<int>& A) {
    if(A.empty()) return 0;
    //[index, [difference, count]]
    vector<unordered_map<int,int>> dp(A.size());
    
    int res = 0;
    for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < i; ++j){
            if((long)A[i] - (long)A[j] > INT_MAX || (long)A[i] - (long)A[j] < INT_MIN){
              continue;do not ignore this step, it will help you save time & space to pass OJ.
            }
            int dif = A[i] - A[j];
            dp[i][dif] += 1;
            if(dp[j].find(dif) != dp[j].end()){
                dp[i][dif] += dp[j][dif];
                res += dp[j][dif];
            }
        }
    }
    return res;
}
};
