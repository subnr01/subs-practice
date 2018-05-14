/*

You are given an integer array sorted in ascending order (may contain duplicates),
you need to split them into several subsequences, where each subsequences consist of 
at least 3 consecutive integers. Return whether you can make such a split.

Example 1:
Input: [1,2,3,3,4,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3
3, 4, 5
Example 2:
Input: [1,2,3,3,4,4,5,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3, 4, 5
3, 4, 5
Example 3:
Input: [1,2,3,4,4,5]
Output: False
Note:
The length of the input is in range of [1, 10000]

*/


//THIS IS MORE A GREEDY QUESTION AND NOT A HEAP QUESTION.
// WILL BE INEFFEICEINT TO DO USING HEAP, REFER OTHER SOLNs.
//Is this O(nlogn) or O(n)
bool isPossible(vector<int>& nums) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> seqs;
        
        for (int i = 0; i < nums.size();) {          
            while (!seqs.empty() && nums[i] - seqs.top().first > 1) {
                // discard top subsequence as we can't add more elements to it
                if (seqs.top().second < 3) return false;
                seqs.pop();
            }
            
            // Can you see why we are not removing element
            // with the same top, but pushing the new on
            // top of the new one.
            if (seqs.empty() || nums[i] == seqs.top().first) {
                // have to start new subsequence as the new number is equal to the top element
                seqs.push({nums[i++], 1});
            } else {
                // otherwise add the new number to the top subsequence
                int size = seqs.top().second + 1;
                seqs.pop();
                seqs.push({nums[i++], size});
            }
        }
        
        while (!seqs.empty()) {
            if (seqs.top().second < 3) return false;
            seqs.pop();
        }
        
        return true;
    }

//O(n) solution using DP???

class Solution {
public:
    bool isPossible(vector<int>& nums) {
        int n = nums.size(), k = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i]-nums[i-1] > 1) {
                if (!check(nums, k, i)) 
                    return false;
                k = i;
            }
        }
        return check(nums, k, n);
    }
private:
    bool check(vector<int>& nums, int s, int e) {
        int ones = 0, twos = 0, tot = 0;
        for (int i = s+1, cnt = 1; i <= e; i++) {
            if (i < e && nums[i] == nums[i-1])
                cnt++;
            else {
                if (cnt < ones + twos) return false;
                twos = ones;
                ones = max(0, cnt-tot);
                tot = cnt;
                cnt = 1;
            }
        }
        return ones == 0 && twos == 0;
    }
};
