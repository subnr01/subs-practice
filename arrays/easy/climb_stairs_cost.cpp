/*


*/

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to 
reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.

Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].



/*
Solution

There is a clear recursion available: the final cost f[i] to 
climb the staircase from some step i is f[i] = cost[i] + min(f[i+1], f[i+2]). 
This motivates dynamic programming.

Let's evaluate f backwards in order. That way, when we are deciding what 
f[i] will be, we've already figured out f[i+1] and f[i+2]


We can do even better than that. At the i-th step, let f1, f2 be the old value of f[i+1], f[i+2],
and update them to be the new values f[i], f[i+1]. 
We keep these updated as we iterate through i backwards. At the end, we want min(f1, f2).
*/


class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int f1 = 0;
        int f2 = 0;
        int f0 = 0;
        int n = cost.size();
        
        for (int i = 0; i < n; i++) {
            f0 = cost[i] + min(f1, f2);
            f2 = f1;
            f1 = f0;
        }
        
        return min(f1, f2);
    }
};
