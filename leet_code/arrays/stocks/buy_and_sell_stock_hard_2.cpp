/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

*/


class Solution {
public:
    int maxProfit(int k, vector<int> &prices) {
        int len = prices.size();
        if (len<2) return 0;
        if (k>len/2){ // simple case
            int ans = 0;
            for (int i=1; i<len; ++i){
                ans += max(prices[i] - prices[i-1],0);
            }
            return ans;
        }
        int hold[k+1];
        int rele[k+1];
        for (int i=0;i<=k;++i){
            hold[i] = INT_MIN;
            rele[i] = 0;
        }
        int cur;
        for (int i=0; i<len; ++i){
            cur = prices[i];
            for(int j=k; j>0; --j){
                rele[j] = max(rele[j],hold[j] + cur);
                hold[j] = max(hold[j],rele[j-1] - cur);
            }
        }
        return rele[k];
    }
};


public int maxProfit(int k, int[] prices) {
    if(k>=prices.length/2){
        int maxProfit = 0;
        for(int i=1; i<prices.length; i++){
            if(prices[i]>prices[i-1]) maxProfit += prices[i]-prices[i-1];
        }
        return maxProfit;
    }

    int[] maxProfit = new int[k+1];
    int[] lowPrice = new int[k+1];
    for(int i=0; i<lowPrice.length; i++) lowPrice[i]=Integer.MAX_VALUE;
    for(int p : prices){
        for(int i=k; i>=1; i--){
            maxProfit[i] = Math.max(maxProfit[i],p-lowPrice[i]);
            lowPrice[i] = Math.min(lowPrice[i],p-maxProfit[i-1]);
        }
    }
    return maxProfit[k];
}
