/*
Implement pow(x, n).


Example 1:

Input: 2.00000, 10
Output: 1024.00000
Example 2:

Input: 2.10000, 3
Output: 9.26100


*/



class Solution {
public:
    double myPow(double x, int n) {
        if(n<0){
            return (1/x)*myPow(1/x,-(n+1));
        }
        if(n==0)return 1;
        if(n%2==0){
            double temp=myPow(x,n/2);
            return temp*temp;
        }
        else{
            double temp=myPow(x,n/2);
            return x*temp*temp;
        }
    }
};
