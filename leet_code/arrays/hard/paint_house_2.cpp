/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.

Example:

Input: [[1,5,3],[2,9,4]]
Output: 5
Explanation: Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5; 
             Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5. 
             
do in O(n) runtime.

*/


//85
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
    int n = costs.size();
    if(n==0) return 0;
    int k = costs[0].size();
    if(k==1) return costs[0][0];

    vector<int> dp(k, 0);
    int min1, min2;

    for(int i=0; i<n; ++i){
        int min1_old = (i==0)?0:min1;
        int min2_old = (i==0)?0:min2;
        min1 = INT_MAX;
        min2 = INT_MAX;
        for(int j=0; j<k; ++j){
            if(dp[j]!=min1_old || min1_old==min2_old){
                dp[j] = min1_old + costs[i][j];
            }else{//min1_old occurred when painting house i-1 with color j, so it cannot be added to dp[j]
                dp[j] = min2_old + costs[i][j];
            }

            if(min1<=dp[j]){
                min2 = min(min2, dp[j]);
            }else{
                min2 = min1;
                min1 = dp[j];
            }
        }
    }

    return min1;
}
};



//another soln
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if(!costs.size() || !costs[0].size()) return 0;
        vector<vector<int> > dp = costs;
        int preMin = 0, preSecMin = 0, preMinPtr = -1;
        for(int i = 0; i < costs.size(); ++i){
            int curMin = INT_MAX, curSecMin = INT_MAX, curMinPtr = -1;
            for(int j = 0; j < costs[i].size(); ++j){
                int val = (j == preMinPtr ? preSecMin : preMin) + costs[i][j];
                if(val < curMin){
                    curSecMin = curMin;
                    curMinPtr = j;
                    curMin = val;
                }
                else if(val < curSecMin){
                    curSecMin = val;
                }
            }
            preMin = curMin;
            preSecMin = curSecMin;
            preMinPtr = curMinPtr;
        }
        return preMin;
    }
};
