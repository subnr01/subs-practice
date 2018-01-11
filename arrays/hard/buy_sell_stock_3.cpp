/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

*/


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int states[2][4] = {INT_MIN, 0, INT_MIN, 0}; // 0: 1 buy, 1: one buy/sell, 2: 2 buys/1 sell, 3, 2 buys/sells
        int len = prices.size(), i, cur = 0, next =1;
        for(i=0; i<len; ++i)
        {
            states[next][0] = max(states[cur][0], -prices[i]);
            states[next][1] = max(states[cur][1], states[cur][0]+prices[i]);
            states[next][2] = max(states[cur][2], states[cur][1]-prices[i]);
            states[next][3] = max(states[cur][3], states[cur][2]+prices[i]);
            swap(next, cur);
        }
        return max(states[cur][1], states[cur][3]);
    }
};


/* Another solution */

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]) using at most k transactions. 
        // f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
        //          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
        // f[0, ii] = 0; 0 times transation makes 0 profit
        // f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade
        if (prices.size() <= 1) return 0;
        else {
            int K = 2; // number of max transation allowed
            int maxProf = 0;
            vector<vector<int>> f(K+1, vector<int>(prices.size(), 0));
            for (int kk = 1; kk <= K; kk++) {
                int tmpMax = f[kk-1][0] - prices[0];
                for (int ii = 1; ii < prices.size(); ii++) {
                    f[kk][ii] = max(f[kk][ii-1], prices[ii] + tmpMax);
                    tmpMax = max(tmpMax, f[kk-1][ii] - prices[ii]);
                    maxProf = max(f[kk][ii], maxProf);
                }
            }
            return maxProf;
        }
    }
};



/* Java solution -- program creek*/
public int maxProfit(int[] prices) {
	if (prices == null || prices.length < 2) {
		return 0;
	}
 
	//highest profit in 0 ... i
	int[] left = new int[prices.length];
	int[] right = new int[prices.length];
 
	// DP from left to right
	left[0] = 0; 
	int min = prices[0];
	for (int i = 1; i < prices.length; i++) {
		min = Math.min(min, prices[i]);
		left[i] = Math.max(left[i - 1], prices[i] - min);
	}
 
	// DP from right to left
	right[prices.length - 1] = 0;
	int max = prices[prices.length - 1];
	for (int i = prices.length - 2; i >= 0; i--) {
		max = Math.max(max, prices[i]);
		right[i] = Math.max(right[i + 1], max - prices[i]);
	}
 
	int profit = 0;
	for (int i = 0; i < prices.length; i++) {
		profit = Math.max(profit, left[i] + right[i]);
	}
 
	return profit;
}



/* Program creek at most k transactions */
public int maxProfit(int k, int[] prices) {
	if (prices.length < 2 || k <= 0)
		return 0;
 
	//pass leetcode online judge (can be ignored)
	if (k == 1000000000)
		return 1648961;
 
	int[] local = new int[k + 1];
	int[] global = new int[k + 1];
 
	for (int i = 0; i < prices.length - 1; i++) {
		int diff = prices[i + 1] - prices[i];
		for (int j = k; j >= 1; j--) {
			local[j] = Math.max(global[j - 1] + Math.max(diff, 0), local[j] + diff);
			global[j] = Math.max(local[j], global[j]);
		}
	}
 
	return global[k];
}


Another sol
public class Solution {
    public int maxProfit(int[] prices) {
        int hold1 = Integer.MIN_VALUE, hold2 = Integer.MIN_VALUE;
        int release1 = 0, release2 = 0;
        for(int i:prices){                              // Assume we only have 0 money at first
            release2 = Math.max(release2, hold2+i);     // The maximum if we've just sold 2nd stock so far.
            hold2    = Math.max(hold2,    release1-i);  // The maximum if we've just buy  2nd stock so far.
            release1 = Math.max(release1, hold1+i);     // The maximum if we've just sold 1nd stock so far.
            hold1    = Math.max(hold1,    -i);          // The maximum if we've just buy  1st stock so far. 
        }
        return release2; ///Since release1 is initiated as 0, so release2 will always higher than release1.
    }
}
