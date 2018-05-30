/*
There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.

Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

Example:
Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation: 
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready 
to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and 
ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.


*/





//USing heap (check out the soln in the atricle)
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        auto comp = [](vector<int> &a, vector<int> &b) {return a[1] < b[1];};
        sort(courses.begin(), courses.end(), comp);
        int cum = 0;
        int num = 0;
        priority_queue<int> max_queue;
        for (int i = 0; i < courses.size(); ++i) {
            int val = cum + courses[i][0];
            if (val <= courses[i][1]) {
                cum = val;
                ++num;
                max_queue.push(courses[i][0]);
            } else if (!max_queue.empty() && max_queue.top() > courses[i][0]) {
                cum -= max_queue.top() - courses[i][0];
                max_queue.pop();
                max_queue.push(courses[i][0]);
            }
        }
        return num;
    }
};
