/*
Equations are given in the format A / B = k, where A and B are variables represented as strings, 
and k is a real number (floating point number). Given some queries, return the answers. 
If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0. 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , 
where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
The input is always valid. You may assume that evaluating the queries will result in no division by zero
and there is no contradiction.

*/


//4ms
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        vector<double> ans;
        unordered_map<string, unordered_map<string, double>> mp;
        
        for(int i = 0; i < equations.size(); i++) {
            string f = equations[i].first, s = equations[i].second;
            mp[f][s] = values[i];
            mp[s][f] = 1.0 / values[i];
        }
        
        for(int i = 0; i < queries.size(); i++) {
            string f = queries[i].first, s = queries[i].second;
            
            if(mp.count(f) && mp.count(s)) {
                if(f == s) ans.push_back(1.0);
                else {
                    unordered_set<string> visited;
                    ans.push_back(dfs(f, s, mp, visited, 1.0));
                }
            }
            else ans.push_back(-1.0);
        }
        
        return ans;
    }
    
private:
    double dfs(string f, string s, unordered_map<string, unordered_map<string, double>> &mp,
               unordered_set<string> &visited, double val) {
        
        if(mp[f].count(s)) return val * mp[f][s];
        
        for(pair<string, double> p : mp[f]) {
            string str = p.first;
            
            if(visited.count(str) == 0) {
                visited.insert(str);
                // val * p.second is the key
                double cur = dfs(str, s, mp, visited, val * p.second);
                if(cur != -1.0) return cur;
            }
        }
        
        return -1.0;
    }
};


//3ms
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string,unordered_map<string, double>> m;
        vector<double> res;
        for (int i = 0; i < values.size(); ++i)
        {
            string up = equations[i].first;
            string down = equations[i].second;
            m[up].insert(make_pair(down, values[i]));           // up --> down 
            if(values[i]!=0)
                m[down].insert(make_pair(up, 1/values[i]));     // down --> up
        }

        for (auto i : queries)
        {
            unordered_set<string> s;
            string up = i.first;
            string down = i.second;
            double tmp = check(up, down, m, s);
            if(tmp) res.push_back(tmp);
            else res.push_back(-1);
        }
        return res;        
    }
    
    double check(string up, string down, 
                 unordered_map<string,unordered_map<string, double>> &m,
                 unordered_set<string> &s)
    {
        if(m[up].find(down) != m[up].end()) return m[up][down];
        
        // for all outgoing edges from up
        for (auto i : m[up])
        {
            // down is not in s
            // i.first = tentative down
            string tentative_down = i.first;
            if(s.find(tentative_down) == s.end())
            {
                s.insert(tentative_down);
                double tmp = check(tentative_down, down, m, s);
                if(tmp) return i.second * tmp;
            }
        }
        
        return 0;
    }
};

