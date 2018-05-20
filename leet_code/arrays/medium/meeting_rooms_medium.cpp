/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] 

find the minimum number of conference rooms required.
*/



https://discuss.leetcode.com/topic/20971/c-o-n-log-n-584-ms-3-solutions



int minMeetingRooms(vector<Interval>& intervals) {
    vector<int> starts, ends;
    for (auto i : intervals) {
        starts.push_back(i.start);
        ends.push_back(i.end);
    }
    sort(begin(starts), end(starts));
    sort(begin(ends), end(ends));
    int e = 0, rooms = 0, available = 0;
    for (int start : starts) {
        while (ends[e] <= start) {
            ++e;
            ++available;
        }
        available ? --available : ++rooms;
    }
    return rooms;
}
