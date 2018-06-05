/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is 
expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should
take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all 
courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course 
order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 
1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering 
is[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a 
graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.


*/


https://discuss.leetcode.com/topic/17276/20-lines-c-bfs-dfs-solutions

//DFS
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<int> toposort;
        vector<bool> onpath(numCourses, false), visited(numCourses, false);
        for (int i = 0; i < numCourses; i++)
            if (!visited[i] && dfs(graph, i, onpath, visited, toposort))
                return {};
        reverse(toposort.begin(), toposort.end());
        return toposort;
    }
private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre.second].insert(pre.first);
        return graph;
    }
    bool dfs(vector<unordered_set<int>>& graph, int node, vector<bool>& onpath, vector<bool>& visited, vector<int>& toposort) { 
        if (visited[node]) return false;
        onpath[node] = visited[node] = true; 
        for (int neigh : graph[node])
            if (onpath[neigh] || dfs(graph, neigh, onpath, visited, toposort))
                return true;
        toposort.push_back(node);
        onpath[node] = false;
        return false;
    }
};

//BFS
class Solution {
public:
    vector<int> findOrder(int N, vector<pair<int, int>>& pre) {
        vector<vector<int>> graph(N,vector<int>());
        vector<int> in(N,0),ans;
        for(auto p:pre){
            graph[p.second].push_back(p.first);
            in[p.first]++;
        }
        queue<int> q;
        for(int i=0;i<N;i++)
            if(in[i]== 0)  q.push(i);
        while(!q.empty()){
            int tmp = q.front();
            ans.push_back(tmp);
            q.pop();
            for(auto i:graph[tmp]){
                in[i]--;
                if(in[i]==0)    q.push(i);
            }
        }
        
        if(ans.size()!=N) 
        {
            return {};
        } else {
            return ans;
        }
    }
};

