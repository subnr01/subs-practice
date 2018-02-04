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
            //low = 1, high = 6, mid = 3
            //low = 1, high = 2, mid = 1
            // low = 2, high = 2, mid = 2
            int mid = low + (high - low)/2;
            if(mid == x/mid)
                return mid;
            else if(mid > x/mid) {
                //3 > 2, so high = 2 and low = 1
                high = mid - 1;
            }
            else if(mid < x/mid)
            {
                //1 < 6, low = 2
                //2 < 3, low = 3, ans = mid(1) + 1 = 2
                low = mid + 1;
                //DO NOT FORGET THIS
                ans = mid;
            }
        }
        return ans;
        
    }
};
