/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

*/

//Recursion with Memoziation
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
Time complexity : O(n). Size of recursion tree can go upto nn
Space complexity : O(n). The depth of recursion tree can go upto nn.

//Dynamic programming soln
public class Solution {
    public int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        int first = 1;
        int second = 2;
        for (int i = 3; i <= n; i++) {
            int third = first + second;
            first = second;
            second = third;
        }
        return second;
    }
}
//Time complexity O(n)
//Space complexity O(n)


//Fibonacci number
public class Solution {
    public int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        int first = 1;
        int second = 2;
        for (int i = 3; i <= n; i++) {
            int third = first + second;
            first = second;
            second = third;
        }
        return second;
    }
}
//Time complexity is O(n)
//Space Complexity is O(1)

//Brute force
public class Solution {
    public int climbStairs(int n) {
        climb_Stairs(0, n);
    }
    public int climb_Stairs(int i, int n) {
        if (i > n) {
            return 0;
        }
        if (i == n) {
            return 1;
        }
        return climb_Stairs(i + 1, n) + climb_Stairs(i + 2, n);
    }
}

//Complexity O(2^n), Size of recursion tree will be 2^n

