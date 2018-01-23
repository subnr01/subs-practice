/*
Given an array of n positive integers and a positive integer s, find the minimal length of 
a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.

*/


// 12 ms
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& a) {
        
        int len = a.size();
        
        if (!len) {
            return 0;
        }
        
        int i = 0;
        int j = 0;
        int sum = 0;
        int min_len = INT_MAX;
        
        while(j<len) {
            if ( sum < s) {
                sum += a[j++];
            } else {
                if (i == j-1) {
                    return 1;
                }
                min_len = (j-i) < min_len? (j-i): min_len;
                sum-=a[i++];
            }
        }
        
        while (sum >= s) {
            min_len = (j-i) < min_len? (j-i): min_len;
            sum -=a[i++];
        }
        
        return min_len == INT_MAX? 0: min_len;
    }
};




// 9 ms
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int N = nums.size();
        if(N == 0) return 0;
        
        int i = 0, j = 0, sum = 0;
        int res = N+1;
        
        for(int j = 0; j < N; ++j)
        {
            sum += nums[j];
            
            while(sum >= s)
            {
                int len = j-i+1;
                res = min(len, res);

                sum -= nums[i];
                ++i;
            }
        }
        
        return res > N? 0: res;
    }
};
