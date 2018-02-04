/*

Given a set of intervals, for each of the interval i, check if there exists an interval j
whose start point is bigger than or equal to the end point of the interval i, which can be 
called that j is on the "right" of i.

For any interval i, you need to store the minimum interval j's index, which means that the 
interval j has the minimum start point to build the "right" relationship for interval i. If 
the interval j doesn't exist, store -1 for the interval i. Finally, you need output the stored 
value of each interval as an array.

Note:
You may assume the interval's end point is always bigger than its start point.
You may assume none of these intervals have the same start point.
Example 1:
Input: [ [1,2] ]

Output: [-1]

Explanation: There is only one interval in the collection, so it outputs -1.
Example 2:
Input: [ [3,4], [2,3], [1,2] ]

Output: [-1, 0, 1]

Explanation: There is no satisfied "right" interval for [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point;
For [1,2], the interval [2,3] has minimum-"right" start point.
Example 3:
Input: [ [1,4], [2,3], [3,4] ]

Output: [-1, 2, -1]

Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point.


*/


//binary search soln
vector<Interval> _intervals;
bool cmp(int &l, int &r)
{
    return _intervals[l].start <= _intervals[r].start;
}
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        if(intervals.empty()) return vector<int>();
        int N = intervals.size();
        if(N == 1) return vector<int>(1,-1);
        
        _intervals = intervals;
        
        vector<int> idx(N,0);
        for(int i = 0; i < N; ++i)
            idx[i] = i;
        
        sort(idx.begin(), idx.end(), cmp);
        
        vector<int> res(N, -1);
        for(int i = 0; i < N; ++i)
        {
            int target = intervals[i].end;
            int pos = bs(idx, target);
            res[i] = pos;
        }
        
        return res;
    }
    

    
    int bs(vector<int> &idx, int x)
    {
        int l = 0, r = idx.size()-1;
        
        while(l <= r)
        {
            int m = l+(r-l)/2;
            
            if(_intervals[idx[m]].start == x)
                return idx[m];
            else if(_intervals[idx[m]].start < x)
                l = m+1;
            else
                r = m-1;
        }
        
        return l == idx.size()? -1: idx[l];
    }
};



//Slower soln using map
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        map<int, int> hash;
        vector<int> res;
        int n = intervals.size();
        for (int i = 0; i < n; ++i)
            hash[intervals[i].start] = i;
        for (auto in : intervals) {
            auto itr = hash.lower_bound(in.end);
            if (itr == hash.end()) res.push_back(-1);
            else res.push_back(itr->second);
        }
        return res;
    }
};
