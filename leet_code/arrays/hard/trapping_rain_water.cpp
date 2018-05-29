/*

Refer leetcode

*/


//Related topics: two pointers, stack


//standard 2 pointer soln
class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size() - 1; 
        int maxLeft = 0, maxRight = 0; 
        
        int res = 0; 
        
        while (left < right) {
            if (height[left] <= height[right]) {
                maxLeft = max(maxLeft, height[left]); 
                res += maxLeft - height[left];
                left++;
            } else {
                maxRight = max(maxRight, height[right]); 
                res += maxRight - height[right]; 
                right--; 
            }
        }
        
        return res; 
    }
};
