/*
There is a garden with N slots. In each slot, there is a flower. The N flowers will bloom one by one in N days.
In each day, there will be exactly one flower blooming and it will be in the status of blooming since then.

Given an array flowers consists of number from 1 to N. Each number in the array represents the place where the
flower will open in that day.

For example, flowers[i] = x means that the unique flower that blooms at day i will be at position x, where i 
and x will be in the range from 1 to N.

Also given an integer k, you need to output in which day there exists two flowers in the status of blooming, 
and also the number of flowers between them is k and these flowers are not blooming.

If there isn't such day, output -1.

Example 1:
Input: 
flowers: [1,3,2]
k: 1
Output: 2
Explanation: In the second day, the first and the third flower have become blooming.
Example 2:
Input: 
flowers: [1,2,3]
k: 1
Output: -1

*/

//Related topics
//array, binary search tree


//nlogn
class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        set<int> bloom;
        for (int i = 0; i < flowers.size(); i++) {
            int p = flowers[i];
            auto it = bloom.insert(p).first;
            if (it != bloom.begin()) {
                if (p-*(--it) == k+1) return i+1;
                it++;
            }
            if (++it != bloom.end() && *it-p == k+1) return i+1; 
        }
        return -1;
    }
};


//Sliding window

/*
1. days[x] = y means that the unique flower at position x will bloom at day y.
2. Now the problem is changed to be:

whether there are k flowers between position x1 and x1 + k + 1 blooming later than both flowers at position x1 and x1 + k + 1.
3. Why saying one pass? Consider the following conditions:

when some days[x1 + i] < min(days[x1], days[x1 + k + 1]) s.t. 0 < i <= k: it means that the flower at position x1 + i 
might bloom earlier than all those between position x1 and x1 + i including x1, obviously neither of these flowers can 
meet 2, so it's no need backtracking and just move x1 to x1 + i, and go forward.

when all days[x1 + i] > min(days[x1], days[x1 + k + 1]) s.t. 0 < i <= k: it means that all the previous flowers will
bloom later than the flower at position x1 + k + 1, also just move x1 to x1 + k + 1 and go ahead.

Thus, the solution costs O(N) time and O(N) space.
*/


class Solution {
public:
    int kEmptySlots(vector<int>& flowers, int k) {
        int m = flowers.size();
        vector<int> days(m);
        for (int i = 0; i < m; ++i)
            days[flowers[i] - 1] = i;
        int i = 0, j = i + k + 1, day = INT_MAX;
        // one pass
        while (j < m) {
            int dday = max(days[i++], days[j]);
            while (days[i] > dday && i < j) ++i;
            if (i == j) day = min(day, dday);
            j = i + k + 1;
        }
        if (day != INT_MAX) return day + 1;
        return -1;
    }
};

