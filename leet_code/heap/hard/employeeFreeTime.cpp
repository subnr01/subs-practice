/*
We are given a list schedule of employees, which represents the working time for each employee.

Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order.

Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

Example 1:
Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation:
There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:
Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]

*/

//Related topics:  heap, greedy

//soln1 54 ms
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
       vector<Interval> res;
        if(schedule.empty()) {
            return res;
        }
        vector<pair<int,int>> intervals;
       for(int i=0;i<schedule.size();i++) {
           for(Interval& interval: schedule[i]) {
                intervals.push_back({interval.start, interval.end});
           }
       }
       sort(intervals.begin(), intervals.end());

        pair<int,int> pre = intervals[0];
        for(int i=1;i<intervals.size();i++){
            if(intervals[i].first>pre.second) {
                res.push_back(Interval(pre.second, intervals[i].first));
                pre = intervals[i];
            } else {
                pre.second = max(pre.second, intervals[i].second);
            }
        }
        return res;
    }
};


///proririty queue not needed for this question, it is an overkill
// anways 
class CompareDist
{
public:
    bool operator()(Interval n1, Interval n2) {
        return n1.start > n2.start;
    }
};



class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        vector<Interval> ret;
        
        if(schedule.size() == 0)
            return ret;
        
        priority_queue<Interval,vector<Interval>,CompareDist> pq;

        for(auto& v : schedule) {
            for(auto& i : v)
                pq.push(i);
        }
        
        ret.push_back(pq.top());
        pq.pop();
        
        while(pq.empty() == false){
            if(pq.top().start >= ret.back().start && pq.top().start <= ret.back().end){
                ret.back().end = max(ret.back().end, pq.top().end);
            }
            else{
                ret.push_back(pq.top());
            }
            pq.pop();
        }
        
        for(int i=1; i<ret.size(); ++i){
            ret[i-1].start = ret[i-1].end;
            ret[i-1].end = ret[i].start;
        }
        
        ret.pop_back();
        return ret;
        
    }
};
