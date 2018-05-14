/*
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime 
list primes of size k. For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the
sequence of the first 12 super ugly numbers given primes = [2, 7, 13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
(4) The nth super ugly number is guaranteed to fit in a 32-bit signed integer.

*/


//Below is heap soln that is complex and ineffeicient, if there are duplicates.
//Take a look at this soln
class Solution {
public:
    
    int minCandidateIndex(vector<int>& input) {
        int min = INT_MAX;
        int minIndex = 0;
        for (int i = 0; i < input.size(); ++i) {
            if (input[i] < min) {
                min = input[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int size = primes.size();
        vector<int> mults(size, 1);
        vector<int> candidates(primes);
        int *dp = new int[n];
        int nUgly = 1;
        dp[0] = 1;
        
        for (int i = 1; i < n; ++i) {
            int mdx = minCandidateIndex(candidates);
            nUgly = candidates[mdx];
            dp[i] = nUgly;
            
            for (int j = 0; j < candidates.size(); ++j) {
                if (nUgly == candidates[j]) {
                    candidates[j] = dp[mults[j]++] * primes[j];
                }
            }
            
        }
        return nUgly;
    }
};




//https://discuss.leetcode.com/topic/31005/my-priority_queue-based-c-code-276ms

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int K = primes.size(), res[n], pIdx[n], lastMul[n] ={}, i, curVal, curIdx;

        priority_queue<pair<int, int>> headHeap; // 
        for(res[0]=-1, i=0; i<K;++i)   headHeap.push(make_pair(-primes[i], i)); // first the ugly number value (change to negative to get the minimum one), second is the index of ugly number queues, i.e. candidates[i]

        for(i=1;i<n;++i)
        {
            curVal = headHeap.top().first;
            curIdx = headHeap.top().second;
            headHeap.pop();
            res[i] = curVal; pIdx[i] = curIdx; // pIdx is the index of the maximum prime factor
            while(pIdx[++lastMul[curIdx]]>curIdx); // skip ugly numbers whose maximum factor index is larger than curIdx.
            headHeap.push(make_pair(res[lastMul[curIdx]] * primes[curIdx], curIdx));
        }
        return -res[n-1];
    }
};
