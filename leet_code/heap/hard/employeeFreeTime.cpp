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
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        
        vector<Interval>res={};
        priority_queue<pair<int,int>, vector<pair<int,int>> , greater<pair<int,int>>>__intervals={};
        int _size = schedule.size();
        
        if(_size == 0)
            return res;
            
        //Create a min_heap
        for(int i=0; i<_size; i++){
            //cout << schedule[i].start << endl;
            for(int j=0;j<schedule[i].size();j++)
                __intervals.push(make_pair(schedule[i][j].start,schedule[i][j].end));
        }
        
        
        int f_start = __intervals.top().first;
        int f_end = __intervals.top().second;
        __intervals.pop();
            
        while(!__intervals.empty()){
            int temp_start = __intervals.top().first;
            int temp_end = __intervals.top().second;
            
            if(temp_start > f_end){
                //new standard to create a new object in the vector of type T.
                res.push_back({f_end,temp_start});
                f_start = temp_start;
                f_end = temp_end;
            }
            else if(temp_start <= f_end){
                f_end = f_end > temp_end ? f_end : temp_end;
            }
            __intervals.pop();
        }
        
        
        return res;
    }
};
