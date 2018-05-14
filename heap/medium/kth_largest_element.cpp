/*
Find the kth largest element in an unsorted array. Note that it is the 
kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.

*/


//https://discuss.leetcode.com/topic/15256/4-c-solutions-using-partition-max-heap-priority_queue-and-multiset-respectively/2


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //LOOK HOW PRIORITY QUEUE IS INTIALISED WITH VECTOR CONTENTS
        priority_queue<int> pq(nums.begin(), nums.end());
        //See how there is no equal sign here.
        for (int i = 0; i < k - 1; i++)
            pq.pop(); 
        return pq.top();
    }
};
