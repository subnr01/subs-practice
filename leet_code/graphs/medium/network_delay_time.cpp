/*
There are N network nodes, labelled 1 to N.

Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node,
v is the target node, and w is the time it takes for a signal to travel from source to target.

Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal?
If it is impossible, return -1.

Note:
N will be in the range [1, 100].
K will be in the range [1, N].
The length of times will be in the range [1, 6000].
All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 1 <= w <= 100.
*/

//Using heap (68 ms)
 int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        int n = times.size();
        unordered_map<int,vector<pair<int,int>> > dic;
        for(int i=0; i<n; i++){
            dic[times[i][0]].push_back(make_pair(times[i][1], times[i][2]));
        }
        auto cmp = [](const pair<int,int>& p1, const pair<int,int>& p2){return p1.second > p2.second;};
        priority_queue< pair<int,int>, vector<pair<int,int>>, decltype(cmp)> heap(cmp);
        heap.push(make_pair(K,0));
        vector<bool> visited(N+1,false);
        int res = 0;
        int cnt=0;
        while(!heap.empty()&&cnt!=N){
            auto node = heap.top();
            heap.pop();
            if(visited[node.first] == false)    cnt++;
            visited[node.first]=true;
            res = node.second;
            if(dic.count(node.first)){
                 for(auto& neighbor:dic[node.first]){
                    if(!visited[neighbor.first]) heap.push(make_pair(neighbor.first, node.second+neighbor.second)); 
                 }
            }
        }
        return cnt==N?res:-1; 
    }

//68 ms
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<int>> mp(N+1, vector<int>(N+1, -1));
        for (const auto& time: times) {
            mp[time[0]][time[1]] = time[2];
        }

        vector<int> dist(N+1, INT_MAX);
        dist[K] = 0;
        auto compare = [&dist](int a, int b) {
            return dist[a] > dist[b];
        };
        priority_queue<int, vector<int>, decltype(compare)> q(compare);

        q.push(K);
        while (!q.empty()) {
            int cur = q.top();
            q.pop();
            for (int i=1; i<=N; ++i) {
                if (mp[cur][i]>=0 && dist[cur]+mp[cur][i] < dist[i]) {
                    dist[i]=dist[cur]+mp[cur][i];
                    q.push(i);
                }
            }
        }
        int ret =0;
        for (int i=1; i<=N; ++i) {
            ret = max(dist[i], ret);
        }
        return ret==INT_MAX?-1:ret;
    }
};
    
    //Alexander: level order BFS (109 ms) 
    class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<int> waits(N + 1, INT_MAX);
        map<int, map<int, int>> adj;
        for (auto e : times) adj[e[0]][e[1]] = e[2];
        queue<int> q;
        q.push(K);
        waits[K] = 0;
        while (!q.empty()) {
            set<int> set;
            for (int n = q.size(); n > 0; n--) {
                int u = q.front(); q.pop();
                for (pair<int, int> nb : adj[u]) {
                    int v = nb.first;
                    if (waits[u] + adj[u][v] < waits[v]) {
                        if (!set.count(v)) {
                            set.insert(v);
                            q.push(v);
                        }
                        waits[v] = waits[u] + adj[u][v];
                    }
                }
            }
        }
        int maxwait = 0;
        for (int i = 1; i <= N; i++)
            maxwait = max(maxwait, waits[i]);
        return maxwait == INT_MAX ? -1 : maxwait;
    }
};



//bellman ford (308 ms)
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<int> dist(N + 1, INT_MAX);
        dist[K] = 0;
        for (int i = 0; i < N; i++) {
            for (vector<int> e : times) {
                int u = e[0], v = e[1], w = e[2];
                if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        int maxwait = 0;
        for (int i = 1; i <= N; i++)
            maxwait = max(maxwait, dist[i]);
        return maxwait == INT_MAX ? -1 : maxwait;
    }
};
