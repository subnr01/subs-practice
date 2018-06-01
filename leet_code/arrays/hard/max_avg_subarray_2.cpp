/*
Given an array consisting of n integers, find the contiguous subarray whose length is greater than or
equal to k that has the maximum average value. And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation:
when length is 5, maximum average value is 10.8,
when length is 6, maximum average value is 9.16667.
Thus return 12.75.

*/

//Related topics: Array, binary search


//https://leetcode.com/problems/maximum-average-subarray-ii/discuss/105477/C++-Clean-binary-search-solution-with-explanation
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double left = INT_MAX, right = INT_MIN, mid;
        for(int num:nums){
            right = max(right, double(num));
            left = min(left, double(num));
        }
        while(left + 0.00001 < right){
            mid = left + (right - left)/2;
            if(islarger(nums, mid, k)){
                right = mid;
            } else {
                left = mid;
            }
        }
        return left;
    }
    
    //Return true when mid is larger than or equal to the maximum average value;
    //Return false when mid is smaller than the maximum average value.
    bool islarger(vector<int>& nums, double mid, int k){
        // sum: the sum from nums[0] to nums[i];
        // prev_sum:  the sum from nums[0] to nums[i-k];
        // min_sum: the minimal sum from nums[0] to nums[j] ( 0=< j  <= i-k );
        double sum = 0, prev_sum = 0, min_sum = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i] - mid;
            if(i >= k){
                prev_sum += nums[i-k] - mid;                        
                min_sum = min(prev_sum, min_sum); 
            }
            if(i >= k-1 && sum > min_sum)return false;
        }
        return true;                                               
    }
};


//Using queue (very fast)
class Solution {
    double getDensity(vector<int>& nums, int i, int j){
        return (double(nums[j+1])-double(nums[i]))/double(j-i+1);
    }
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int N = nums.size();
        nums.insert(nums.begin(), 0);
        for (int i=1; i<nums.size(); i++){
            nums[i] += nums[i-1];
        }
        deque<int> index;
        double result = INT_MIN;
        for (int j=k-1; j<N; j++){
            while(index.size()>=2 && getDensity(nums, index.back(), j-k)<=getDensity(nums, index[index.size()-2], index.back()-1)){
                index.pop_back();
            }
            index.push_back(j-k+1);
            while(index.size()>=2 && getDensity(nums, index[0], j)<=getDensity(nums, index[1], j)){
                index.pop_front();
            }
            double value = getDensity(nums, index[0], j);
            result = max(result, value);
        }
        return result;
    }
};

