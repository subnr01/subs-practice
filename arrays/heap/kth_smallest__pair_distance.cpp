/*
Given an integer array, return the k-th smallest distance among all the pairs.
The distance of a pair (A, B) is defined as the absolute difference between A and B.

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



\\x`Bucket sort, O(n^2)
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size(), N = 1000000;
        vector<int> cnt(N, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) 
                cnt[abs(nums[i]-nums[j])]++;
        }
        for (int i = 0; i < N; i++) {
            if (cnt[i] >= k) return i;
            k -= cnt[i];
        }
        return 0;
    }
};


\\Binary search, O(nlogn)
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


//Heap
class Solution {
    public int smallestDistancePair(int[] nums, int k) {
        Arrays.sort(nums);
        PriorityQueue<Node> heap = new PriorityQueue<Node>(nums.length,
            Comparator.<Node> comparingInt(node -> nums[node.nei] - nums[node.root]));
        for (int i = 0; i + 1 < nums.length; ++i) {
            heap.offer(new Node(i, i+1));
        }

        Node node = null;
        for (; k > 0; --k) {
            node = heap.poll();
            if (node.nei + 1 < nums.length) {
                heap.offer(new Node(node.root, node.nei + 1));
            }
        }
        return nums[node.nei] - nums[node.root];
    }
}
class Node {
    int root;
    int nei;
    Node(int r, int n) {
        root = r;
        nei = n;
    }
}
Complexity Analysis

/*

*/
