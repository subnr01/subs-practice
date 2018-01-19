/*
Given a char array representing tasks CPU need to do. It contains capital letters 
A to Z where different letters represent different tasks.Tasks could be done without original order.
Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at
least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

*/


//Related topics:  Queue, Greedy


//https://zhuhan0.blogspot.com/2017/07/leetcode-621-task-scheduler.html
//https://leetcode.com/problems/task-scheduler/solution/


//Alexander

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> counts;
        for (char t : tasks) {
            counts[t]++;
        }
        priority_queue<int> pq;
        for (pair<char, int> count : counts) {
            pq.push(count.second);
        }
        int alltime = 0;
        int cycle = n + 1;
        while (!pq.empty()) {
            int time = 0;
            vector<int> tmp;
            for (int i = 0; i < cycle; i++) {
                if (!pq.empty()) {
                    tmp.push_back(pq.top());
                    pq.pop();
                    time++;
                }
            }
            for (int cnt : tmp) {
                if (--cnt) {
                    pq.push(cnt);
                }
            }
            alltime += !pq.empty() ? cycle : time;
        }
        return alltime;
    }
};

