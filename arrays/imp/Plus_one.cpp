/*

Given a non-negative number represented as an array of digits, plus one to the number.

*/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int sz = digits.size();
        
        for (auto i = sz - 1; i >= 0; i--) {
            if (digits[i] == 9) {
                digits[i] = 0;
            }
            else {
                digits[i]+=1;
                return digits;
            }
        }
        digits[0] = 1;
        digits.push_back(0);
        return digits;
    }
};
