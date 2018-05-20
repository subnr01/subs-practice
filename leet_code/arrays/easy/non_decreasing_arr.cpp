/*

Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.

*/


class Solution {
public:
    bool checkPossibility(vector<int>& a) {
        int modified = 0;
        int prev = a[0];
        
        for(int i = 0; i < a.size(); i++){
            if(a[i] < prev && modified++) {
                return false;
            }
            
            if(a[i] < prev && (i-2) >= 0 && a[i-2] > a[i]) {
                continue;
            }
            prev = a[i];
        }
        return true;
    }
};
