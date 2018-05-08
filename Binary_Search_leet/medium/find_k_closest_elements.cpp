/*
Given a sorted array, two integers k and x, find the k closest elements to x in the array. 
The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

Example 1:
Input: [1,2,3,4,5], k=4, x=3
Output: [1,2,3,4]


Example 2:
Input: [1,2,3,4,5], k=4, x=-1
Output: [1,2,3,4]

*/

// good soln
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // find the index of the first element 
        // that is equal to or greater than x
        int index = std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int i = index - 1;
        int j = index;                                    
        while(k--) 
        {
            if (i<0 || (j<arr.size() && abs(arr[i] - x) > abs(arr[j] - x) )) {
                j++;
            } else {
                i--;
            }
        }
        return vector<int>(arr.begin() + i + 1, arr.begin() + j );
    }
};


//difficult solution hard to comprehend
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0;
        int right = arr.size() - k;
        
        while (left < right)
        {
            int mid = (left + right)/2;
            if (x -arr[mid] > arr[mid + k] - x) 
            {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};


