/*
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

*/


class Solution {
public:
    int reverse(int x) {
        long long res = 0;
        while(x) {
            res = res*10 + x%10;
            x /= 10;
        }
        return (res<INT_MIN || res>INT_MAX) ? 0 : res;
    }
};
