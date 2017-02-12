/*

Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/

string removeKdigits(string num, int k) {
        string sol;
        if (k >= num.length()) return "0";
        
        // while the last number is larger than the new one, 
        // keep poping out the last number until a smaller one appears
        // e.g. 1234567890 k=3
        for (int i = 0; i < num.length(); i++){
            while (sol.length() != 0 && k > 0 && sol.back() > num[i]){
                sol.pop_back();
                k--;
            }
            sol.push_back(num[i]);
        }
        
        // for monotonically increasing string
        // discard the last k digits
        // e.g. 123456 k=3
        while (k != 0){
            k--;
            sol.pop_back();
        }
        
        // for sol with leading zeros
        // e.g. 10200 k=1
        while(sol[0] == '0') sol.erase(0,1);
        
        return sol.length() == 0 ? "0" : sol;
        
    }
