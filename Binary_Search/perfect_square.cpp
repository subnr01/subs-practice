/*

Given a positive integer num, write a function which returns True if num is a perfect square else False.



*/


class Solution {
public:
   bool isPerfectSquare(int num) {
    int l = 0, r = num;
    while(l <= r) {
        long long mid = (l + r) / 2;
        if(mid * mid < num)
            l = mid + 1;
        else if(mid * mid > num)
            r = mid - 1;
        else
            return true;
    }
    
    return false;
}
};
