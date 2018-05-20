/*

Given an array consists of non-negative integers, 
your task is to count the number of triplets chosen from the array that can make triangles 
if we take them as side lengths of a triangle.


Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
Note:
The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].


*/


// how to check for a triangle
// sum of two sides must be greater than the third side
//my soln

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int count = 0;
        for ( int k = nums.size() - 1; k > 1; --k ) {
            int i = 0, j = k - 1;
            int value = nums[k];
            while ( i < j ) {
                if ( nums[i] + nums[j] > value ) {
                    // it is not j's distance, but i's distance
                    count += j - i;
                    --j;
                
                } else {
                    ++i;
                }
            }
        }
        return count;
    }
};


//2 Pointers O(n^2logn)
// space complexity: O(logn) for sorting
class Solution {
public:
    int triangleNumber(vector<int>& a) {
        int n = a.size();
        sort(a.begin(), a.end());
        int res = 0;
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int sum = a[i] + a[j];   // the sum of 2 shortest sides;
                int firstGE = firstGreatOrEqual(a, j + 1, sum);
                res += firstGE - 1 - j;
            }
        }
        return res;
    }

private:
    int firstGreatOrEqual(vector<int>& a, int i0, int target) {
        int lo = i0, hi = a.size();
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (a[mid] < target) {
                lo = mid + 1;
            }
            else {
                hi = mid;
            }
        }
        return hi;
    }
};


//2 Pointers O(n^2)
// space complexity: O(logn)  for sorting

class Solution {
public:
    int triangleNumber(vector<int>& a) {
        int res = 0;
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());    // a is decreasing
        for (int i = 0; i + 2 < a.size(); i++) {
            for (int j = i + 1, k = a.size() - 1; j < k; j++) {
                while (j < k && a[j] + a[k] <= a[i]) {
                    k--;
                }
                res += k - j;
            }
        }
        return res;
    }
};
