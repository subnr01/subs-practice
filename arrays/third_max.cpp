/*

Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, 
return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
*/


class Solution {
public:
    int thirdMax(vector<int>& nums) {
    set<int> top3;
    for (int num : nums) {
        top3.insert(num);
        if (top3.size() > 3)
            top3.erase(top3.begin());
    }
    return top3.size() == 3 ? *top3.begin() : *top3.rbegin();
}
};

