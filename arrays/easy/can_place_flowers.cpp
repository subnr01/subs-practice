/*
Given a flowerbed (represented as an array containing 0 and 1, where 
0 means empty and 1 means not empty), and a number n, return if n new flowers 
can be planted in it without violating the no-adjacent-flowers rule.

Example 1:
Input: flowerbed = [1,0,0,0,1], n = 1
Output: True

Example 2:
Input: flowerbed = [1,0,0,0,1], n = 2
Output: False

*/

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int m) {
        int n = flowerbed.size();
        int i = 0;
        int count = 0;
        
        while(i < n) {
            if(flowerbed[i] == 0 && (i == 0 || flowerbed[i-1] == 0) && 
               (i == n - 1 || flowerbed[i+1] == 0))
               {
                   flowerbed[i]=1;
                   count ++;
               }
               i++;
        }
        return count >= m;
    }
};
