/*

Given an integer, write a function to determine if it is a power of two.

*/



class Solution {
public:
    bool isPowerOfTwo(int n) {
        
        if (n <= 0) {
            return false;
        }
        
        if (!(n & n-1)) {
            return true;
        }
        return !(n & (n-1));
    }
};
