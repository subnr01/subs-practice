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


//Another soln
class Solution {
public:
    int findIntegers(int num) {
         
        int ans[32];
        ans[0] = 1, ans[1] = 2;
        
        for(int i = 2; i < 32; i++){
            ans[i] = ans[i-1] + ans[i-2];
        }
        
        int i = 30, lastBit = 0, sum = 0;
        
        while(i >= 0){
            if((num & (1<<i)) != 0){
                sum += ans[i];
                
                if(lastBit){
                    sum--;
                    break;
                }
                
                lastBit = 1;
            }
            else lastBit = 0;
            
            i--;
        }
        
        return sum+1;
    }
};
