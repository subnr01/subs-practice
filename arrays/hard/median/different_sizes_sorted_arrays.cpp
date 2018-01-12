/*
Median of different size sorted arrays
*/

http://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/
// /https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2481/


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        int m = nums1.size();
        int n = nums2.size();
        
        int total = (m + n);
        
        if (total % 2 == 0) {
            //If it is even, then we need to take average.
            //k is the middle index
            return (findKth(nums1, nums2, 0, 0, total/2) + findKth(nums1, nums2, 0, 0, total/2 + 1) )/2.0;
        } else {
            //Since this is one large array and odd, (m+1)th index should suffice.
            return findKth(nums1, nums2, 0, 0, total/2 + 1);
        }
        
    }
    
    int findKth (vector<int> &nums1, vector<int> &nums2, int s1, int s2, int k)
    {
        if (s1 >= nums1.size()) {
            //k distance from s2, (-1) because array begins from 0.
            return nums2[s2 + k - 1];
        }
        
        if (s2 >= nums2.size()) {
            //k distance from s2, (-1) because array begins from 0.
            return nums1[s1 + k - 1];
        }
        
        if (k == 1) {
            //
            return min(nums1[s1],nums2[s2]);
        }
        //Move to the middle
        int m1 = s1 + k/2 -1;
        int m2 = s2 + k/2 -1;
        
        int mid1 = m1 < nums1.size() ?nums1[m1] :INT_MAX;
        int mid2 = m2 < nums2.size() ?nums2[m2] :INT_MAX;
        
        if (mid1 < mid2) {
            //we have looked at m1, so (m1 + 1)
            return findKth (nums1, nums2, m1 + 1, s2, k - k/2);
        } else {
            //we have looked at m2, so (m2 + 1)
            return findKth (nums1, nums2, s1, m2 + 1, k - k/2);
        }
            
    }
};
}
