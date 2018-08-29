












//https://leetcode.com/problems/shortest-path-visiting-all-nodes/discuss/135680/My-C++-solution-with-explanation-(Floyd-+-State-Compression-DP)
//Solution 1 using  (Floyd + State Compression DP) (15ms)
class Solution {
public:
    
    int dis[15][15];
    int dp[1<<13][13];
    
    void floyd(int n) {
        for(int k=0; k<n; k++)
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
    }
    int DP(int n) {
        memset(dp, 0x3f, sizeof(dp));
        for (int i=0; i<n; i++)
            dp[1<<i][i] = 0;
        for (int group=1; group<(1<<n); group++)
            for (int u=0; u<n; u++)
                for (int v=0; v<n; v++) {
                    int src = 1 << u, dst = 1 << v;
                    if ((group & src) && !(group & dst))
                        dp[group|dst][v] = min(dp[group][u] + dis[u][v], dp[group|dst][v]);
                }
        int min_dis = 0x3f3f3f3f;
        for (int i=0; i<n; i++)
            min_dis = min(dp[(1<<n)-1][i], min_dis);
        return min_dis;
    }
    
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        memset(dis, 0x3f, sizeof(dis));
        for (int i=0; i<n; i++) {
            int to_size = graph[i].size();
            for (int j=0; j<to_size; j++) {
                int u = i, v = graph[i][j];
                dis[u][v] = 1;
            }
        }
        floyd(n);
        int min_dis = DP(n);
        return min_dis;
    }
};


/dfs (10ms)
class Solution {
public:
    
    void dfs(vector<int>&visited,int count,vector<int>&cur,int &res,vector<vector<int>>&graph){
        if(res == graph.size()){
            return;
        }
        
        if(count == graph.size()){
            res = min(res,(int)cur.size());
            return;
        }
        if(cur.size() >= res){
            return;
        }
        int min_ = INT_MAX;
        int src = cur.back();
        for(auto &i : graph[src]){
            min_ = min(min_,visited[i]);
        }
        
        for(auto &i : graph[src]){
            if(min_ == visited[i]){
                cur.push_back(i);
                if(!visited[i]) count++;
                visited[i]++;
                dfs(visited,count,cur,res,graph);
                cur.pop_back();
                visited[i]--;
                if(!visited[i]) count--;
            }
        }   
    }
    
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        if(!n){
            return 0;
        }
        int res = INT_MAX;
        int count = 0;
        vector<int>visited(n,0);
        vector<int>cur;
        
        for(int i = 0;i<n;i++){
            visited[i]++;
            count++;
            cur.push_back(i);
            dfs(visited,count,cur,res,graph);
            visited[i]--;
            count--;
            cur.pop_back();
        }
        return res-1;
    }
};

//BFS (20ms)
class Solution {
public:
    
    // BFS
    int shortestPathLength(vector<vector<int>>& graph) {
        queue<state> q;
        for (int i = 0; i < graph.size(); i++) {
            Solution::state s(i);
            q.push(s);
            m_.insert(s);
        }
        
        while (!q.empty()) {
            state cur = q.front();
            q.pop();
            
            if (cur.covered == (1 << graph.size())-1) {
                    return cur.cost;
            }
            
            for (int dest : graph[cur.node]) {
                state new_s(dest);
                new_s.covered = cur.covered | (1 << dest);
                new_s.cost = cur.cost + 1;
                if (m_.count(new_s) == 0) {
                    m_.insert(new_s);
                    q.push(new_s);
                }
            }
        }
        
        return -1;
    }
    
private:
    struct state {
        int covered;
        int node;
        int cost;
        
        state(int node) : node(node), cost(0) {
            covered = 1 << node;
        }
        
        bool operator==(const state& rhs) const {
            return this->node == rhs.node && this->covered == rhs.covered;
        }
    };
    
    struct hasher {
        size_t operator()(const state& s) const {
            return 1331 * s.covered + 7193 * s.node;
        }
    };

    
    unordered_set<state, hasher> m_;
};
