/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/


class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> res;
        int index = 0;
	 
	    
	/*
	Move till our start is greater than interval element end 
	*/
        while(index < intervals.size() && intervals[index].end < newInterval.start){
            res.push_back(intervals[index++]);
        }
	    
	/*
	If interval start is lesser than our end
	*/
        while(index < intervals.size() && intervals[index].start <= newInterval.end){
		
	   //Update the start with the min of the two	
            newInterval.start = min(newInterval.start, intervals[index].start);
	   //Update the end with the max of the two
            newInterval.end = max(newInterval.end, intervals[index].end);
            index++;
        }
	//Push the new interval
        res.push_back(newInterval);
        while(index < intervals.size()){
	   //Push the remaining intervals
            res.push_back(intervals[index++]);
        }
        return res;
    }
};
