/*
Given a string S of digits, such as S = "123456579", we can split it into a Fibonacci-like sequence [123, 456, 579].

Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:

0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
F.length >= 3;
and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.

Also, note that when splitting the string into pieces, each piece must not have extra leading zeroes,
except if the piece is the number 0 itself.

Example 1:

Input: "123456579"
Output: [123,456,579]
Example 2:

Input: "11235813"
Output: [1,1,2,3,5,8,13]
Example 3:

Input: "112358130"
Output: []
Explanation: The task is impossible.
Example 4:

Input: "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
Example 5:

Input: "1101111"
Output: [110, 1, 111]
Explanation: The output [11, 0, 11, 11] would also be accepted.
*/


class Solution {
public:
    vector<int> splitIntoFibonacci(string S) {
        int n = S.size();
        for(int i = 1; i < n-2; i++){
            
            if(i > 1 && S[0] == '0') {
                break;
            }
            
            long long first = stoll(S.substr(0, i));
            if(first > INT_MAX) {
                break;
            }
            
            for(int j = 1; j < n-i-1; j++)
            {
               
                if(j > 1 && S[i] == '0') {
                    break;
                }
                
                long long second = stoll(S.substr(i, j));
                if(second > INT_MAX) {
                    break;
                }
                
                vector<int> res;
                res.push_back(first);
                res.push_back(second);
                if(isValid(first, second, S, i+j, res)) {
                    return res;
                }
            }
        }
        return {};
    }
    
    bool isValid(int first, int second, string &S, int start, vector<int> &res){
        if (start == S.size()) {
            return true;
        }
        
        long long sum = first + second;
        if(sum > INT_MAX) {
            return false;
        }
        
        string target = to_string(sum);
        if(S.size()-start < target.size()) {
            return false;
        }
        
        string curr = S.substr(start, target.size());
        if(curr != target) {
            return false;
        }
        
        res.push_back(sum);
        return isValid(second, sum, S, start+target.size(), res);
     }
};
