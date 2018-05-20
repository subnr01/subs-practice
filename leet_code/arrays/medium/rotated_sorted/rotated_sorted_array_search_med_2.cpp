/*
Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.

*/
class Solution {
public:
    bool search(vector<int>& a, int target) {
        
        int sz = a.size();
        if (!sz) {
            return false;
        }
        
        int high = sz - 1;
        int low  = 0;
        
        while (low <= high) {
            int mid = (high - low)/2 + low;
            
            if (a[mid] == target) return true;
            
            if (a[mid] > a[high]) {
                if (a[mid] >target && target >= a[low]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
                
            } else if (a[mid] < a[high]) {
                if (a[mid] < target && target <= a[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else {
                high--;
            }
            
        }
        return a[low] == target?true:false;
    }
};
