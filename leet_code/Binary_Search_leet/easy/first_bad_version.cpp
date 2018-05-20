/*
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

*/

class Solution {
public:
    int firstBadVersion(int n) {
        int low = 1;
        int high = n;
        
        while (low <= high)
        {
            int mid = (high - low)/2 + low;
            
            if (isBadVersion(mid) == false) {
                low = mid + 1;
            } else
            {
                high = mid - 1;
            }
        }
        return low;
    }
};
