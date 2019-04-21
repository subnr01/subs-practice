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


/*
Solution (DFS)
Since pair<int, int> is inconvenient for the implementation of graph algorithms, we first transform it to a graph.
    If course u is a prerequisite of course v, we will add a directed edge from node u to node v.
vector<bool> visited to record all the visited nodes
vector<bool> onpath to record the visited nodes of the current DFS visit

*/
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) 
    {
        graph g(numCourses);
        for (auto p : prerequisites) {
            g[p.second].push_back(p.first);
        }
        
        vector<int> visited(numCourses, false);
        for (int i = 0; i < numCourses; i++) {
            if (!acyclic(g, visited, i)) {
                return false;
            }
        }
        return true;
    }
private:
    typedef vector<vector<int>> graph;
    
    
    bool acyclic(graph& g, vector<int>& visited, int node) {
        if (visited[node] > 0 ) {
            return visited[node] == 2;
        }
   
        visited[node] = 1;
        for (int v : g[node]) {
            if (!acyclic(g, visited, v)) {
                return false;
            }
        }
        visited[node] = 2;
        return true;
    }
};




//fastest BFS
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




