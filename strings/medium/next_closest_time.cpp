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


//Java soln
  int diff = 0x3f3f3f3f;
    String result = "";
    int h;
    int m;
    public String nextClosestTime(String time) {
        int[] digit = new int[4];
        int tot = 0;
        String[] val = time.split(":");
        int hour = Integer.parseInt(val[0]);
        int minu = Integer.parseInt(val[1]);
        digit[tot++] = hour / 10;
        digit[tot++] = hour % 10;
        digit[tot++] = minu / 10;
        digit[tot++] = minu % 10;

        h = hour;
        m = minu;

        dfs(digit, 0, new int[4]);

        return result;
    }

    void dfs(int[] digit, int i, int[] ans) {
        if (i == 4) {
            int hour = 10 * ans[0] + ans[1];
            int minu = 10 * ans[2] + ans[3];
            if (hour >= 0 && hour <= 23 && minu >= 0 && minu <= 59) {
                int df = diff(hour, minu);
                if (df < diff) {
                    diff = df;
                    result = valid(hour) + ":" + valid(minu);
                }
            }
        }
        else {
            for (int j = 0; j < 4; ++j) {
                ans[i] = digit[j];
                dfs(digit, i + 1, ans);
            }
        }
    }

    int diff(int hour, int minu) {
        int c2o = 60 * 60 - h * 60 - m;
        int n2o = 60 * 60 - hour * 60 - minu;
        return n2o < c2o ? c2o - n2o : c2o - n2o + 3600;
    }

    public String valid(int time) {
        if (time >= 0 && time <= 9) return "0" + time;
        else return time + "";
    }
