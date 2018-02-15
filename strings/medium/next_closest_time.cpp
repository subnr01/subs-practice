/*
Given a time represented in the format "HH:MM", form the next closest 
time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" 
are all valid. "1:34", "12:9" are all invalid.

Example 1:

Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39,
which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. 
It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.

*/





class Solution {
public:
    string nextClosestTime(string time) {
        vector<int> d = {
            time[0] - '0', time[1] - '0', time[3] - '0', time[4] - '0' };
        
        int h = d[0] * 10 + d[1];
        int m = d[2] * 10 + d[3];
        vector<int> curr(4, 0);
        int now = toTime(h, m);
        int best = now;
        
        dfs(0, d, curr, now, best);
        char buff[5];
        sprintf(buff, "%02d:%02d", best / 60, best % 60);
        return string(buff);
    }
private:
    void dfs(int dep, const vector<int>& digits, vector<int>& curr, int time, int& best) {
        if (dep == 4) {
            int curr_h = curr[0] * 10 + curr[1];
            int curr_m = curr[2] * 10 + curr[3];
            if (curr_h > 23 || curr_m > 59) return;
            int curr_time = toTime(curr_h, curr_m);
            //Look at timediff, it is not your usual difference calculation
            if (timeDiff(time, curr_time) < timeDiff(time, best))
                best = curr_time;
            return;
        }            
        
        for (int digit : digits) {
            curr[dep] = digit;
            dfs(dep + 1, digits, curr, time, best);
        }        
    }
    
    int toTime(int h, int m) {
        return h * 60 + m;
    }
    
    int timeDiff(int t1, int t2) {
        if (t1 == t2) return INT_MAX;
        return ((t2 - t1) + 24 * 60) % (24 * 60);
    }
};






//Alexander
//WEll this runs 1440 * x times, but is a brilliant solution. 
// There is a optimised soln that can run only 256 times.
class Solution {
    int mins[4] = { 600, 60, 10, 1 };
public:
    string nextClosestTime(string time) {
        size_t colon = time.find(':');
        int cur = stoi(time.substr(0, colon)) * 60 + stoi(time.substr(colon + 1));
        string next = "0000";
        for (int i = 1, d = 0; i <= 1440 && d < 4; i++) {
            int m = (cur + i) % 1440;
            for (d = 0; d < 4; d++) {
                next[d] = '0' + m / mins[d]; m %= mins[d];
                if (time.find(next[d]) == string::npos) break;
            }
        }
        return next.substr(0, 2) + ':' + next.substr(2, 2);
    }
};
