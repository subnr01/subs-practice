/*

Example 1:
Input: 
pid =  [1, 3, 10, 5]
ppid = [3, 0, 5, 3]
kill = 5
Output: [5,10]
Explanation: 
           3
         /   \
        1     5
             /
            10
Kill 5 will also kill 10.

*/



//DFS
class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        vector<int> killed;
        map<int, set<int>> children;
        for (int i = 0; i < pid.size(); i++) {
            children[ppid[i]].insert(pid[i]);
        }
        killAll(kill, children, killed);
        return killed;
    }

private:
    void killAll(int pid, map<int, set<int>>& children, vector<int>& killed) {
        killed.push_back(pid);
        for (int child : children[pid]) {
            killAll(child, children, killed);
        }
    }
};

//BFS
class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        vector<int> killed;
        map<int, set<int>> children;
        for (int i = 0; i < pid.size(); i++) {
            children[ppid[i]].insert(pid[i]);
        }

        queue<int> q;
        q.push(kill);
        while (!q.empty()) {
            int p = q.front(); q.pop();
            killed.push_back(p);
            for (int child : children[p]) {
                q.push(child);
            }
        }

        return killed;
    }
};

