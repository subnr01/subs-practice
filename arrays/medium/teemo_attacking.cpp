/*
Refer leetcode for problem explanation
*/

/* 
Problem is relatively simple though question is very big and verbose
*/


class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if(timeSeries.size() == 0) return 0;
        int begin = timeSeries[0], total = 0;
        for(auto t : timeSeries) {
            total += t < begin + duration ? t- begin : duration;
            begin = t;
        }
        return total + duration;
    }
};
