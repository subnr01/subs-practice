/*

Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to
Venture Capital, LeetCode would like to work on some projects to increase its capital before 
the IPO. Since it has limited resources, it can only finish at most k distinct projects before
the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most
k distinct projects.

You are given several projects. For each project i, it has a pure profit Pi and a minimum capital 
of Ci is needed to start the corresponding project. Initially, you have W capital. When you finish
a project, you will obtain its pure profit and the profit will be added to your total capital.

To sum up, pick a list of at most k distinct projects from given projects to maximize your final
 capital, and output your final maximized capital.

Example 1:
Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

Output: 4

Explanation: Since your initial capital is 0, you can only start the project indexed 0.
             After finishing it you will obtain profit 1 and your capital becomes 1.
             With capital 1, you can either start the project indexed 1 or the project indexed 2.
             Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
             Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
Note:
You may assume all numbers in the input are non-negative integers.
The length of Profits array and Capital array will not exceed 50,000.
The answer is guaranteed to fit in a 32-bit signed integer.

*/


//2 priority queue  O(NlgN) solution
//https://discuss.leetcode.com/topic/77768/very-simple-greedy-java-solution-using-two-priorityqueues/2
// Can you rewrite this in C++.
public class Solution {
    public int findMaximizedCapital(int k, int W, int[] Profits, int[] Capital) {
        PriorityQueue<int[]> pqCap = new PriorityQueue<>((a, b) -> (a[0] - b[0]));
        PriorityQueue<int[]> pqPro = new PriorityQueue<>((a, b) -> (b[1] - a[1]));
        
        for (int i = 0; i < Profits.length; i++) {
            pqCap.add(new int[] {Capital[i], Profits[i]});
        }
        
        for (int i = 0; i < k; i++) {
            while (!pqCap.isEmpty() && pqCap.peek()[0] <= W) {
                pqPro.add(pqCap.poll());
            }
            
            if (pqPro.isEmpty()) break;
            
            W += pqPro.poll()[1];
        }
        
        return W;
    }
}

//Sorting and priority queue
/*
There are many excellent solutions based on two priority queue solution, 
however, we do not need to maintain two priority queues that contain all projects.

If we sort the Capital in increasing order, we can insert "doable" project into
the pq until we meet an "undoable" project.

We need only one priority queue (multiset) to maintain the "doable" projects. Here the 
key observation is: we can only pop k times. So we do not need to maintain a large priority queue. Every time we find the size of PQ is larger than k (k is shrinking!!!), we just erase the project with least profit from the PQ.

Note that the worst case time complexity is still O(NlogN), because we need to sort : )
*/
class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& P, vector<int>& C) {
      priority_queue<int> low;      // P[i]'s within current W
      multiset<pair<int,int>> high; // (C[i],P[i])'s' outside current W
      
      for (int i = 0; i < P.size(); ++i) // initialize low and high
        if(P[i] > 0) if (C[i] <= W) low.push(P[i]); else high.emplace(C[i], P[i]);
    
      while (k-- && low.size()) { 
        W += low.top(), low.pop(); // greedy to work on most profitable first
        for (auto i = high.begin(); high.size() && i->first <= W; i = high.erase(i)) low.push(i->second);
      }
      return W;
}

};



//Stefan
//Keep a max-heap of current possible profits. Insert possible profits as
soon as their needed capital is reached.

def findMaximizedCapital(self, k, W, Profits, Capital):
    current = []
    future = sorted(zip(Capital, Profits))[::-1]
    for _ in range(k):
        while future and future[-1][0] <= W:
            heapq.heappush(current, -future.pop()[1])
        if current:
            W -= heapq.heappop(current)
    return W
    
    
