/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like
(ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple
transactions at the same time (ie, you must sell the stock before you buy again).

*/


class Solution {
public:
    int maxProfit(vector<int> &prices) {
    int sum = 0;
    for (size_t p = 1; p < prices.size(); ++p) 
      sum = sum + max(prices[p] - prices[p - 1], 0);    
    return sum;
}
};

//Another version
// DP solution, buy[i] indicates profit on time i with stock bought, sell[i] indicates profit at time i with stock sold.
// So buy[i] = max(buy[i - 1], sell[i - 1] - price[i] - fee), buy[i - 1] indicates don't buy stock at time i.
// sell[i - 1] - price[i] - fee means buy stock at time i.
// sell[i] = max(sell[i - 1], buy[i - 1] + price), arguments mean don't sell stock on time i and sell stock on time i.
// The result is sell[n] since sell is always large than buy.
// Since dp[i] only relies on dp[i - 1], so we can reduce the memory use to O(1).
// The time complexity is O(n).
class Solution {
 public:
  int maxProfit(vector<int>& prices, int fee) {
    int buy = INT_MIN, sell = 0;
    for (int price : prices) {
      int tmp = sell;
      sell = max(sell, buy + price);
      buy = max(buy, tmp - price - fee);
    }
    return sell;
  }
};


//Another version
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int cash = 0, hold = -prices[0];
        for (int i = 1; i < prices.size(); i++) {
            cash = std::max(cash, hold + prices[i] - fee);
            hold = std::max(hold, cash - prices[i]);
        }
        return cash;
    }
};
