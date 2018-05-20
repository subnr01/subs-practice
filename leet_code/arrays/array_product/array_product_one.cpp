/*

Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of 
all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

*/


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int fromBegin=1;
        int fromLast=1;
        vector<int> res(n,1);
        
        for(int i=0;i<n;i++){
            res[i]=res[i]*fromBegin;
            fromBegin=fromBegin*nums[i];
            res[n-1-i]=res[n-1-i]*fromLast;
            fromLast=fromLast*nums[n-1-i];
        }
        return res;
    }
};
