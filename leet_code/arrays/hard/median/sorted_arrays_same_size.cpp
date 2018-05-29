/*

Median of two sorted arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5


*/
https://discuss.leetcode.com/topic/4996/share-my-o-log-min-m-n-solution-with-explanation/6

/* This function returns median of ar1[] and ar2[].
   Assumptions in this function:
   Both ar1[] and ar2[] are sorted arrays
   Both have n elements */
//REWRITE THIS USING VECTOR
int getMedian(int ar1[], int ar2[], int n)
{
    /* return -1  for invalid input */
    if (n <= 0)
        return -1;
    if (n == 1)
        return (ar1[0] + ar2[0])/2;
    if (n == 2)
        return (max(ar1[0], ar2[0]) + min(ar1[1], ar2[1])) / 2;
 
    int m1 = median(ar1, n); /* get the median of the first array */
    int m2 = median(ar2, n); /* get the median of the second array */
 
    /* If medians are equal then return either m1 or m2 */
    if (m1 == m2)
        return m1;
 
    /* if m1 < m2 then median must exist in ar1[m1....] and
        ar2[....m2] */
    if (m1 < m2)
    {
        if (n % 2 == 0)
            return getMedian(ar1 + n/2 - 1, ar2, n - n/2 +1);
        return getMedian(ar1 + n/2, ar2, n - n/2);
    }
 
    /* if m1 > m2 then median must exist in ar1[....m1] and
        ar2[m2...] */
    if (n % 2 == 0)
        return getMedian(ar2 + n/2 - 1, ar1, n - n/2 + 1);
    return getMedian(ar2 + n/2, ar1, n - n/2);
}
 
/* Function to get median of a sorted array */
int median(int arr[], int n)
{
    if (n%2 == 0)
        return (arr[n/2] + arr[n/2-1])/2;
    else
        return arr[n/2];
}


//Using findKth
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        int total = (m + n);
        
        if (total % 2 == 0) {
            return (findkth(nums1, nums2, 0, 0, total/2) + findkth(nums1, nums2, 0, 0, total/2 + 1) )/2.0; 
        } else { 
            return findkth(nums1, nums2, 0, 0, total/2 + 1);
        }
    }
    
    int findkth (vector<int>& nums1, vector<int>& nums2, int s1, int s2, int k) 
    {
        if (s1 >= nums1.size()) {
            return nums2[s2 + k -1];
        }
        
        if (s2 >= nums2.size()) {
            return nums1[s1 + k -1];
        }
        
        if (k == 1) {
            return min(nums1[s1], nums2[s2]);
        }
        
        int m1 = s1 + k/2 - 1;
        int m2 = s2 + k/2 - 1;
        
        int mid1 = m1 < nums1.size()? nums1[m1]: INT_MAX;
        int mid2 = m2 < nums2.size()? nums2[m2]: INT_MAX;
        
        if (mid1 < mid2) {
            return findkth(nums1, nums2, m1 + 1, s2, k - k/2);
        } else {
            return findkth(nums1, nums2, s1, m2 + 1, k - k/2);
        }
        
        
    }
    
};

