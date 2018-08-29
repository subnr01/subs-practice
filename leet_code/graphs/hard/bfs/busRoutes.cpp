/*

We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. 
For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) 
travels in the sequence 1->5->7->1->5->7->1->... forever.

We start at bus stop S (initially not on a bus), and we want to go to bus stop T.
Travelling by buses only, what is the least number of buses we must take to reach our destination? 
Return -1 if it is not possible.

Example:
Input: 
routes = [[1, 2, 7], [3, 6, 7]]
S = 1
T = 6
Output: 2
Explanation: 
The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.

*/

//What is this soln
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (routes.empty()) return -1;
        if (S == T) return 0;
        
        unordered_map<int, vector<int>> m;
        for (int i=0; i < routes.size(); ++i) 
            for (const int stop: routes[i])
                m[stop].push_back(i);
        
        vector<int> visited(routes.size(), 0);
        queue<int> q;
        q.push(S);
        int buses = 0;
        
        while (!q.empty()) {
            int size = q.size();
            ++buses;
            while (size--) {
                int curr = q.front(); q.pop();
                for (const int bus: m[curr]) {
                    if (visited[bus]) continue;
                    visited[bus] = 1;
                    for (int stop: routes[bus]) {
                        if (stop == T) return buses;
                        q.push(stop);
                    }
                }
            }
        }
            return -1;
    }

};
