/*

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is 
expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 
you should also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph
is represented.
You may assume that there are no duplicate edges in the input prerequisites.

*/


https://discuss.leetcode.com/topic/17273/18-22-lines-c-bfs-dfs-solutions/3


Solution (DFS)
Since pair<int, int> is inconvenient for the implementation of graph algorithms, we first transform it to a graph.
    If course u is a prerequisite of course v, we will add a directed edge from node u to node v.

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<bool> onpath(numCourses, false), visited(numCourses, false);
        for (int i = 0; i < numCourses; i++)
            if (!visited[i] && dfs_cycle(graph, i, onpath, visited))
                return false;
        return true;
    }
private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre.second].insert(pre.first);
        return graph;
    } 
    bool dfs_cycle(vector<unordered_set<int>>& graph, int node, vector<bool>& onpath, vector<bool>& visited) {
        if (visited[node]) return false;
        onpath[node] = visited[node] = true; 
        for (int neigh : graph[node])
            if (onpath[neigh] || dfs_cycle(graph, neigh, onpath, visited))
                return true;
        
        onpath[node] = false;
        return false;
    }
};

Solution (BFS) ( uses topological sort);
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph = make_graph(numCourses, prerequisites);
        vector<int> degrees = compute_indegree(graph);
        for (int i = 0; i < numCourses; i++) {
            int j = 0;
            for (; j < numCourses; j++)
                if (!degrees[j]) break;
            if (j == numCourses) return false;
            degrees[j] = -1;
            for (int neigh : graph[j])
                degrees[neigh]--;
        }
        return true;
    }
private:
    vector<unordered_set<int>> make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> graph(numCourses);
        for (auto pre : prerequisites)
            graph[pre.second].insert(pre.first);
        return graph;
    }
    vector<int> compute_indegree(vector<unordered_set<int>>& graph) {
        vector<int> degrees(graph.size(), 0);
        for (auto neighbors : graph)
            for (int neigh : neighbors)
                degrees[neigh]++;
        return degrees;
    }
};



//fastest
class Solution {
public:
    bool canFinish(int N, vector<pair<int, int>>& pre) {
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
        if(ans.size()!=N) return false;
        else return true;
    }
};

