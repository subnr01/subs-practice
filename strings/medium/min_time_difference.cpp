/*

Given a list of 24-hour clock time points in "Hour:Minutes" format,
find the minimum minutes difference between any two time points in the list.
Example 1:
Input: ["23:59","00:00"]
Output: 1


*/


//n log n solution
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int n = timePoints.size();
        if (n > 1440) return 0;
        vector<int> times;
        for (int i = 0; i < n; i++) 
            times.push_back(to_min(timePoints[i]));
        sort(times.begin(), times.end());
        int ans = times[0]+60*24-times.back();
        for (int i = 1; i < n; ++i) {
            ans = min(ans, times[i]-times[i-1]);
        }
        return ans;
    }
private:
    int to_min(string& a) {
        int h = (a[0]-'0')*10+(a[1]-'0'), m = (a[3]-'0')*10+(a[4]-'0');
        return 60*h+m;
    }
};

//array solution without using sorting
public class Solution {
    public int findMinDifference(List<String> timePoints) {
        boolean[] mark = new boolean[24 * 60];
        for (String time : timePoints) {
            String[] t = time.split(":");
            int h = Integer.parseInt(t[0]);
            int m = Integer.parseInt(t[1]);
            if (mark[h * 60 + m]) return 0;
            mark[h * 60 + m] = true;
        }
        
        int prev = 0, min = Integer.MAX_VALUE;
        int first = Integer.MAX_VALUE, last = Integer.MIN_VALUE;
        for (int i = 0; i < 24 * 60; i++) {
            if (mark[i]) {
                if (first != Integer.MAX_VALUE) {
                    min = Math.min(min, i - prev);
                }
                first = Math.min(first, i);
                last = Math.max(last, i);
                prev = i;
            }
        }
        
        min = Math.min(min, (24 * 60 - last + first));
        
        return min;
    }
}

