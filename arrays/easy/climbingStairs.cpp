/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

*/


class Solution {
public:
    map <int, int> curry = {
        {1, 1}, {2, 2}
    };
    int climbStairs(int n) {
        int num = curry[n];
        if (num) return num;
        num = climbStairs(n - 1) + climbStairs(n - 2);
        curry[n] = num;
        return num;
    }
};
