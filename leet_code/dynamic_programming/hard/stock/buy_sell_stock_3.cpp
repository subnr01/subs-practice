/*

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:

Input: [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
             Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
Example 2:

Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.
Example 3:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

*/

class Solution {
public:
    int maxProfit(vector<int>& prices, int k = 2) {
        if(prices.empty())
            return 0;
        
        int d = prices.size();
        vector<vector<int>> dp(k+1, vector<int>(d, 0));
        
        for(int r = 1; r <= k; r++)
        {
            int tempMax = INT_MIN;
            for(int c = 1; c < d; c++)
            {
                tempMax = max(tempMax, dp[r-1][c - 1] - prices[c - 1]);
                dp[r][c] = max(dp[r][c-1], tempMax + prices[c]);
            }
        }
        
        return dp[k][d-1];
    }
};
