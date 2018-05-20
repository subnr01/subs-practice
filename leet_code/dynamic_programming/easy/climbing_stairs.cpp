
/*


You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Note: Given n will be a positive integer.


Example 1:

Input: 2
Output:  2
Explanation:  There are two ways to climb to the top.

1. 1 step + 1 step
2. 2 steps
Example 2:

Input: 3
Output:  3
Explanation:  There are three ways to climb to the top.

1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step


*/


class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) {
            return n;
        }
        
        int dp[n];
        dp[0] = 1;
        dp[1] = 2;
        
        for (int i = 2; i < n; i++)
        {
            dp[i] = dp[i - 1] + dp [i - 2];
        }
        
        return dp[n - 1];
        
    }
};



//Without using a dp array
class Solution {
public:
    int climbStairs(int n) {
        int StepOne = 1;
        int StepTwo = 0;
        int ret = 0;
        for(int i=0;i<n;i++)
        {
            ret = StepOne + StepTwo;
            StepTwo = StepOne;
            StepOne = ret;
        }
        return ret;
    }
};

//Brute force
public class Solution {
    public int climbStairs(int n) {
        int memo[] = new int[n + 1];
        return climb_Stairs(0, n, memo);
    }
    public int climb_Stairs(int i, int n, int memo[]) {
        if (i > n) {
            return 0;
        }
        if (i == n) {
            return 1;
        }
        if (memo[i] > 0) {
            return memo[i];
        }
        memo[i] = climb_Stairs(i + 1, n, memo) + climb_Stairs(i + 2, n, memo);
        return memo[i];
    }
}



