/*

This question is the same as "Max Chunks to Make Sorted" except the integers of the given array 
are not necessarily distinct, the input array could be up to length 2000, and the elements could be up to 10**8.

Given an array arr of integers (not necessarily distinct), we split the array into 
some number of "chunks" (partitions), and individually sort each chunk.  
After concatenating them, the result equals the sorted array.

What is the most number of chunks we could have made?

Example 1:

Input: arr = [5,4,3,2,1]
Output: 1
Explanation:
Splitting into two or more chunks will not return the required result.
For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.
Example 2:

Input: arr = [2,1,3,4,4]
Output: 4
Explanation:
We can split into two chunks, such as [2, 1], [3, 4, 4].
However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.

*/

Related topics: sliding window, array


//sort version, see the other version for the faster one
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int sum1 = 0, sum2 = 0, ans = 0;
        vector<int> t = arr;
        sort(t.begin(), t.end());
        for(int i = 0; i < arr.size(); i++) {
            sum1 += t[i];
            sum2 += arr[i];
            if(sum1 == sum2) ans++;
        }
	return ans;
    }
};


//another soln
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        
        std::vector<int> lmax(arr.size(), 0);
        std::vector<int> rmin(arr.size() , 0);
        
        int mx = INT_MIN;
        int mn = INT_MAX;
        for(int i = 0 ; i < arr.size() ; i++)
        {
            mx = std::max(mx , arr[i]);
            lmax[i] = mx;
        }
        
        for(int i = arr.size()-1 ; i>=0 ; i--)
        {
            mn = std::min(mn , arr[i]);
            rmin[i] = mn;
        }
        
        int res = 1;
        for(int i = 0 ; i < arr.size()-1; i++)
        {
            if(lmax[i] <= rmin[i+1])
            {
                res++;
            }
        }
        return res;
    }
};
