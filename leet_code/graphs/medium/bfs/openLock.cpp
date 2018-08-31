

//alexander (closer to the standard soln)

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        set<string> dead(deadends.begin(), deadends.end());
        
        if (dead.find("0000") != dead.end()) {
            return -1;
        }
        
        if (target == "0000") {
            return 0;
        }
        
        queue<string> q;
        unordered_set<string> v;
        q.push("0000");
        int step = 1;
        
        while (!q.empty())
        {
            int n = q.size();
            for (int i = 0; i < n; i++)
            {
                string cur = q.front();
                q.pop();
                for (int j = 0; j < 4; j++)
                {
                    for (int dif = 1; dif <= 9; dif += 8)
                    {
                        string s = cur;
                        s[j] = (s[j] - '0' + dif) % 10 + '0';
                        if (s == target) {
                            return step;
                        }
                        if (!dead.count(s) && !v.count(s)) {
                            q.push(s);
                        }
                        v.insert(s);
                    }
                }
            }
            step++;
        }
        return -1;
    }
};
