/*
Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)

Your car drives automatically according to a sequence of instructions A (accelerate) and R (reverse).

When you get an instruction "A", your car does the following: position += speed, speed *= 2.

When you get an instruction "R", your car does the following: if your speed is positive then speed = -1 , 
otherwise speed = 1.  (Your position stays the same.)

For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.

Now for some target position, say the length of the shortest sequence of instructions to get there.

Example 1:
Input: 
target = 3
Output: 2
Explanation: 
The shortest instruction sequence is "AA".
Your position goes from 0->1->3.
Example 2:
Input: 
target = 6
Output: 5
Explanation: 
The shortest instruction sequence is "AAARA".
Your position goes from 0->1->3->7->7->6.

*/

//Related topics: heap, DP


//Check other solns, there seems no heap soln
class Solution {
public:    
    int racecar(int target) {
        vector<int> dp(target+1,INT_MAX);
        dp[0] = 0;
        
        for(int i = 1;i <= target;i++){
            int m = 1,j = 1;
            for(;j < i;j = (1 << m) - 1){
                int q = 0;
                for(int p = 0;p < j;p = (1 << q)-1){
                    dp[i] = min(dp[i],m+1+q+1+dp[i-(j-p)]);
                    q++;
                }
                m++;
            }
            dp[i] = min(dp[i],m + (i == j ? 0 : 1 + dp[j-i]));
        }
        
        return dp[target];
    }
};

//Check the below link for detailed explanations
https://leetcode.com/problems/race-car/discuss/124326/Summary-of-the-BFS-and-DP-solutions-with-intuitive-explanation


//BFS solution
#define P first
#define S second
using PII=pair<int,int>;
using QPII=queue<PII>;
class Solution {
    struct hash { size_t operator()(const PII& x) const { return x.P*100000+x.S; } };
public:
    int racecar(int T, QPII q=QPII({make_pair(0,1)})) {
        unordered_set<PII, hash> v({q.front()});
        for (int d=0,N=(int)q.size(); ;++d,N=(int)q.size()) while (N--){ // process all N nodes at each depth d
            auto x=q.front(); q.pop();
            if (x.P==T) return d;
            auto A=make_pair(x.P + x.S,x.S * 2);
            if (!v.count(A) && abs(A.P - T) < T){ // prune A by position
                q.push(A);
                v.insert(A);
            }
            auto R=make_pair(x.P,(x.S > 0) ? -1 : 1);
            if (!v.count(R)){
                q.push(R);
                v.insert(R);
            }
        }
        return -1;
    }
};
