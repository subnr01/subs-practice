/*

Given a positive integer n, find the number of non-negative integers less than or equal to n, 
whose binary representations do NOT contain consecutive ones.

Example 1:
Input: 5
Output: 5
Explanation: 
Here are the non-negative integers <= 5 with their corresponding binary representations:
0 : 0
1 : 1
2 : 10
3 : 11
4 : 100
5 : 101
Among them, only integer 3 disobeys the rule (two consecutive ones) and the other 5 satisfy the rule. 

*/


//Java original solution
public class Solution {
    public int findIntegers(int num) {
        StringBuilder sb = new StringBuilder(Integer.toBinaryString(num)).reverse();
        int n = sb.length();
        
        int a[] = new int[n];
        int b[] = new int[n];
        a[0] = b[0] = 1;
        for (int i = 1; i < n; i++) {
            a[i] = a[i - 1] + b[i - 1];
            b[i] = a[i - 1];
        }
        
        int result = a[n - 1] + b[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            if (sb.charAt(i) == '1' && sb.charAt(i + 1) == '1') break;
            if (sb.charAt(i) == '0' && sb.charAt(i + 1) == '0') result -= b[i];
        }
        
        return result;
    }
}



//C++ solution check
class Solution {
public:
    int findIntegers(int num) {
        int n=1, temp=num, res;
        while ((temp>>1) > 0) {
            n++;
            temp>>=1;
        }
        vector<int> a(n,1), b(n,1);
        for (int i=1; i<n; i++) {
            a[i]=a[i-1]+b[i-1];
            b[i]=a[i-1];
        }
        res=a.back()+b.back();
        for (int i=n-2; i>=0; i--) {
            if (((num>>(i+1))&1)==1 && ((num>>i)&1)==1) break;
            if (((num>>(i+1))&1)==0 && ((num>>i)&1)==0) res-=b[i];
        }
        return res;
    }
};
