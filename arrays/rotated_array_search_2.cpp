/*

Write a function to determine if a given target is in the array.

*/

class Solution {
public:
    bool search(vector<int>& a, int target) {
        
        int sz = a.size();
        
        int high = sz - 1;
        int low  = 0;
        
        while (low < high) {
            int mid = (high - low)/2 + low;
            
            if (a[mid] == target) return true;
            
            if (a[mid] > a[high]) {
                if (a[mid] >target && target >= a[low]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
                
            } else if (a[mid] < a[high]) {
                if (a[mid] < target && target <= a[high]) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            } else {
                high--;
            }
            
        }
        return a[low] == target?true:false;
    }
};

