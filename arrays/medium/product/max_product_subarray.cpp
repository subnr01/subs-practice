/*
Find the contiguous subarray within an array (containing at least one number) which has the largest product.
For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/



class Solution {
public:
    int maxProduct(vector<int>& nums) {
        
        int frontProduct = 1;
        int backProduct = 1;
        size_t n = nums.size();
        
        //THIS REALLY IMPORTANTO
        int ans = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            frontProduct = frontProduct * nums[i];
            backProduct = backProduct * nums[n - 1 -i];
            
            ans = max(max(frontProduct, backProduct) , ans);
            frontProduct = frontProduct == 0? 1: frontProduct;
            backProduct = backProduct == 0? 1: backProduct;
        }
        
        return ans;
        
    }
};
