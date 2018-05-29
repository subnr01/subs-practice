/*
Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B)
is defined as the absolute difference between A and B.

Example 1:
Input:
nums = [1,3,1]
k = 1
Output: 0 
Explanation:
Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.

Note:
2 <= len(nums) <= 10000.
0 <= nums[i] < 1000000.
1 <= k <= len(nums) * (len(nums) - 1) / 2.
*/

//Related topics: Binary search, heap


//binary search popular, read article for heap
//sol1
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        //PLAN 1
        //traverse nums O(n^2) compute all dists
        //find kth smallest O(k)
        
        //PLAN 2
        //function pairNum(int k) : given a dist "d", return how many pairs dist smaller than "d" O(NlogN)
        //binary search "d" from 0 to 1000000 log(1000000)
        //store nums in map, search a+k, pos
        
        //how to implement pairNum(int k)
        //find the first d == k
        std::sort(nums.begin(), nums.end());
        int left = 0, right = nums.back() - nums.front();
        while(left <= right) {
            int mid = left + (right - left) / 2;
            int d = piarNum(nums, mid);
            if(d >= k) {
                right = mid - 1;
            } else if (d < k) {
                left = mid + 1;
            }
        }
        return left;
    }
private:
    //two point
    int piarNum(const vector<int>& nums, int d) {
        //nums[j] - nums[i] < d
        //nums[i+1]
        int j = 0;
        int l = nums.size();
        int ret = 0;
        for(int i = 0; i < l; ++i) {
            //i,j the first valid pair
            while(j < l && nums[j] - nums[i] <= d) j++;
            ret += j - 1 - i;
        }
        return ret;
    }
};


//sol2
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), low = 0, high = 1000000;
        while (low < high) {
            int mid = (low + high)/2, cnt = 0;
            for (int i = 0, j = 0; i < n; i++) {
                while (j < n && nums[j]-nums[i] <= mid) j++;
                cnt += j-i-1;
            }
            if (cnt < k) 
                low = mid+1;
            else
                high = mid;
        }
        return low;
    }
};
