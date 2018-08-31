

//alexander (closer to the standard soln)

/*
The solution in brief:

We push a String into the queue and find all its neighbors:
For example:
"0000" has 8 neighbors where every digit can have two values "1" or "9".
We push all the neigbors into the queue: So that is level 1 and so a step:

And we follow again and put neighbors of all these 8 strings, so we have 64 neighbors 
into the queue. That is step 2.

We also have a visited(hash) and dead(hash) to make sure we do not push
strings which are in these maps into the queue.

Amdist all these, if we find our target we exit out.
Every level we increase 8 times for all the elements in the queue, so at
every level the number of children increases 8 times.
Every time we cross a level, we increment a step.

*/

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
