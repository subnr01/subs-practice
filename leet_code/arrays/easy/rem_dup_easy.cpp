/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length.
Do not allocate extra space for another array, you must do this in place with constant memory.
For example,
Given input array nums = [1,1,2],
Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively. It
doesn't matter what you leave beyond the new length.
*/


Please note this in the problem: It doesn’t matter what you leave beyond the new length.

//In the solution below, the array will still have last element unchanged. Change length to a.size() and 
// see for tourself.
class Solution {
public:
    int removeDuplicates(vector<int>& a) {
        int n = a.size();
        int length = 1;
        if(n < 2) return n;
        for(int i = 1; i < n ; i++)
        {
            if(a[i] != a[i-1]) {
                a[length++] = a[i];
            }
        }
        return length;
        
    }
};
