
/*
In a group of N people (labelled 0, 1, 2, ..., N-1), each person has different amounts of money, and different levels of quietness.

For convenience, we'll call the person with label x, simply "person x".

We'll say that richer[i] = [x, y] if person x definitely has more money than person y.  
Note that richer may only be a subset of valid observations.

Also, we'll say quiet[x] = q if person x has quietness q.

Now, return answer, where answer[x] = y if y is the least quiet person (that is, 
the person y with the smallest value of quiet[y]), among all people who definitely have 
equal to or more money than person x.

 

Example 1:

Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
Output: [5,5,2,5,4,5,6,7]
Explanation: 
answer[0] = 5.
Person 5 has more money than 3, which has more money than 1, which has more money than 0.
The only person who is quieter (has lower quiet[x]) is person 7, but
it isn't clear if they have more money than person 0.

answer[7] = 7.
Among all people that definitely have equal to or more money than person 7
(which could be persons 3, 4, 5, 6, or 7), the person who is the quietest (has lower quiet[x])
is person 7.

The other answers can be filled out with similar reasoning.

*/


class Solution {
public:
    unordered_map<int, vector<int>> richer2;
    vector<int> res;
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        for (auto v : richer) richer2[v[1]].push_back(v[0]);
        res = vector<int> (quiet.size(), -1);
        for (int i = 0; i < quiet.size(); i++) dfs(i, quiet);
        return res;
    }

    int dfs(int i, vector<int>& quiet) {
        if (res[i] >= 0) return res[i];
        res[i] = i;
        for (int j : richer2[i]) if (quiet[res[i]] > quiet[dfs(j, quiet)]) res[i] = res[j];
        return res[i];
    }
};



//BFS
class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<int> in_deg(n, 0);
        vector<vector<int>> e(n, vector<int>());
        for (auto& vec : richer) {
            ++in_deg[vec[1]];
            e[vec[0]].push_back(vec[1]);
        }
        vector<int> ans(quiet.begin(), quiet.end());
        vector<int> idx(n, 0);
        for (int i = 0; i < n; ++i)  idx[i] = i;
        queue<int> Q;
        for (int i = 0; i < n; ++i) {
            if (in_deg[i] == 0)  Q.push(i);
        }
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (int v : e[u]) {
                if (ans[v] > ans[u]) {
                    ans[v] = ans[u];
                    idx[v] = idx[u];
                }
                --in_deg[v];
                if (in_deg[v] == 0) {
                    Q.push(v);
                }
            }
        }
        return idx;
    }
};

