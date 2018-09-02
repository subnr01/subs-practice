/*

Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.

Each person may dislike some other people, and they should not go into the same group. 

Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.

Return true if and only if it is possible to split everyone into two groups in this way.

 

Example 1:

Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
Output: true
Explanation: group1 [1,4], group2 [2,3]
Example 2:

Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
Output: false
Example 3:

Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
Output: false
*/

//DFS Soln
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<int> colors(N, -1);
        vector<vector<int> > graph(N);
        for (auto& v : dislikes) {
            graph[v[0] - 1].push_back(v[1] - 1);
            graph[v[1] - 1].push_back(v[0] - 1);
        }
        for (int i = 0; i < N; i++) {
            if (colors[i] == -1 && !validColor(graph, colors, 0, i))
                return false;
        }
        return true;
    }
    
    bool validColor(vector<vector<int> >& graph, vector<int>& colors, int color, int node) {
        if (colors[node] != -1) 
            return colors[node] == color;
        colors[node] = color;
        for (int next : graph[node]) {
            if (!validColor(graph, colors, 1 - color, next))
                return false;
        }
        return true;
    }
};


//DFS Soln (Faster)
class Solution {
public:
    bool dfs(int i,vector<int> g[],int color[])
    {
        if (color[i]==-1)
        {
            color[i]=0;
            for (int j=0;j<g[i].size();j++)
               {
                if (color[g[i][j]]==color[i])
                   {
                    return false;}
                else if (color[g[i][j]]==-1)
                {
                    color[g[i][j]]=1;
                    if (!dfs(g[i][j],g,color))
                        {return false;}
                }
            }
        }
        else if (color[i]==0)
        {
            for (int j=0;j<g[i].size();j++)
               {
                if (color[g[i][j]]==color[i])
                    {return false;}
                else if (color[g[i][j]]==-1)
                {
                    color[g[i][j]]=1;
                    if (!dfs(g[i][j],g,color))
                        {return false;}
                }
            }
        }
        else
        {
            for (int j=0;j<g[i].size();j++)
               {
                if (color[g[i][j]]==color[i])
                    return false;
                else if (color[g[i][j]]==-1)
                {
                    color[g[i][j]]=0;
                    if (!dfs(g[i][j],g,color))
                        return false;
                }
            }
            
        }
        return true;
        
    }
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<int> g[N];
        int color[N];
        memset(color,-1,N*sizeof(color[0]));
        for (int i=0;i<dislikes.size();i++)
        {
            g[dislikes[i][0]-1].push_back(dislikes[i][1]-1);
            g[dislikes[i][1]-1].push_back(dislikes[i][0]-1);
        }
        for (int i=0;i<N;i++)
        {
            if (color[i]==-1 && (!dfs(i,g,color)))
            {
                return false;
            }
        }
        return true;
    }
};



//BFS Soln
class Solution {
private:
    bool paintBFS(vector<vector<int>>& g,queue<int>& q,vector<int>& color){
        while(!q.empty()){
            int u=q.front();
            q.pop();
            int c=color[u];
            for(auto v:g[u]){
                if(color[v]==0){
                    color[v]=-c;
                    q.push(v);
                }
                else if(color[v]==c)
                    return false;
            }
        }
        return true;
    }
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<vector<int>> g(N+1);
        for(int i=0;i<dislikes.size();++i){
            int u=dislikes[i][0],v=dislikes[i][1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> color(N+1,0);
        for(int i=1;i<=N;++i){
            if(color[i]==0){
                queue<int> q;
                color[i]=1;
                q.push(i);
                if(!paintBFS(g,q,color))
                    return false;
            }
        }
        return true;
    }
};


