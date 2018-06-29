/*
You have k lists of sorted integers in ascending order. Find the smallest 
range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

Example 1:
Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].

*/


//related topics: hash table, string, 2 pointers

//Check out the other solution which is slower complexity
// but does not use the priority queue, which is an optimisation
// Solution is O(n * log m), space complexity is O(m)

/*
the solution is interesting because it uses a priority qeue which makes
things simpler.

.At any point in time, the priority qeueu contains 3 elements from
all the lists whet are the lowest and the highest element give the 
common interval.
The challenge is to udpate the queue, such that at one point we
have the min difference between the lowest and the highest element
in the queue.

The elements in the queue are in ascending order, that means
the first element of the queue is the smallest one.

We pick the smallest one and get the next greater element in the list where it 
belongs, so that our interval cahnges depending on the value of the new lement 
that is inserted.

*/
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        typedef vector<int>::iterator vi;
        
        struct comp {
            bool operator()(pair<vi, vi> p1, pair<vi, vi> p2) {
                return *p1.first > *p2.first;
            }
        };
        
        int lo = INT_MAX, hi = INT_MIN;
        priority_queue<pair<vi, vi>, vector<pair<vi, vi>>, comp> pq;
        for (auto &row : nums) {
            lo = min(lo, row[0]);
            hi = max(hi, row[0]);
            pq.push({row.begin(), row.end()});
        }
        /* 
        state of pq after this, given the input:
          [0] = {
             first = (item = 0)
             second = (item = 1397644077)
           }
          [1] = {
             first = (item = 4)
             second = (item = 320696344)
          }
          [2] = {
             first = (item = 5)
             second = (item = 1397644077)
          }
       */
        
        
        vector<int> ans = {lo, hi};
        //ans = {0 , 5}
        while (true) {
            auto p = pq.top();
            /* 
            p = {0, 1397644077}
            */
            pq.pop();
            /*
            Remember we are storing the pointers,
            so ++p.first becomes 9, given [0,9,12,20]
            */
            
            /*
            If there are the same iterators
            ( begin == end ) after increment, 
            then the current range in ans 
            is the solution
            */
            if (p.first == p.second)
                break;
            pq.push(p); //after pq contains {4,5,9} as its first elements, as 0 is removed and 9 is pushed
            
            lo = *pq.top().first; //lo = 4
            hi = max(hi, *p.first); // high = 9
            if (hi - lo < ans[1] - ans[0])
                ans = {lo, hi}; //ans is (0,5) since (5-0) is not lesser than (9-5)
        }
        return ans;
    }
};


// Solution is O(n * m), space complexity is O(m)
// Convert this to C++.
public class Solution {
    public int[] smallestRange(int[][] nums) {
        int minx = 0, miny = Integer.MAX_VALUE;
        int[] next = new int[nums.length];
        boolean flag = true;
        for (int i = 0; i < nums.length && flag; i++) {
            for (int j = 0; j < nums[i].length && flag; j++) {
                int min_i = 0, max_i = 0;
                for (int k = 0; k < nums.length; k++) {
                    if (nums[min_i][next[min_i]] > nums[k][next[k]])
                        min_i = k;
                    if (nums[max_i][next[max_i]] < nums[k][next[k]])
                        max_i = k;
                }
                if (miny - minx > nums[max_i][next[max_i]] - nums[min_i][next[min_i]]) {
                    miny = nums[max_i][next[max_i]];
                    minx = nums[min_i][next[min_i]];
                }
                next[min_i]++;
                if (next[min_i] == nums[min_i].length) {
                    flag = false;
                }
            }
        }
        return new int[] {minx, miny};
    }
}
