/*
Implement int sqrt(int x).

Compute and return the square root of x.

x is guaranteed to be a non-negative integer.


Example 1:

Input: 4
Output: 2
Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since we want to return an integer, the 
decimal part will be truncated.


*/



class Solution {
public:
    int mySqrt(int x) {
        
        if(x == 0 or x == 1) 
            return x;
        
        int low = 1, high = x;
        int ans;
        
        while(low <= high)
        {
            int mid = low + (high - low)/2;
            if(mid == x/mid)
                return mid;
            else if(mid > x/mid)
                high = mid - 1;
            else if(mid < x/mid)
            {
                low = mid + 1;
                ans = mid;
            }
        }
        return ans;
        
    }
