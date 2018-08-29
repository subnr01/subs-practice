


class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int s, int d, int K) {
       unordered_map<int, vector<pair<int,int>>> g;
       for (const auto& e : flights) {
            g[e[0]].emplace_back(e[1], e[2]);
       }
       int ans = INT_MAX;
       queue<pair<int,int>> q;q.push({s,0}); 
       int steps =0; 
       while(!q.empty())
       {
            int n = q.size();
            for(int i=0; i<n; ++i)
            {
                auto curr=q.front();
                q.pop();
                if(curr.first == d) {
                    ans = min(ans, curr.second); 
                }
                for(auto x:  g[curr.first])
                {             
                    if( curr.second + x.second > ans) {
                        continue;
                    }
                    q.push({x.first,curr.second + x.second });
                }  
            }
            if(steps++ > K) { 
                break;
            }
        }
        
        return ans == INT_MAX ? - 1 : ans;
    } 

};


//Another soln
class Solution {
public:    
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        if(src==dst) return 0;
        vector<vector<Flight>> table(n);
        
        for(auto& f: flights)
        {
            table[f[0]].emplace_back(f[1],f[2]);
        }
        vector<int> visited(n, INT_MAX);

        queue<pair<int,int>> q;
        q.emplace(0,src);
        while(!q.empty() && k>=0)
        {
            --k;
            for(int i=0, size =q.size();i<size;++i)
            {
                int front = q.front().second;
                int total_price = q.front().first;
                q.pop();
                for(auto& p:table[front])
                {
                    int price = total_price+p.price;
                    if(price<visited[p.dest] && price<visited[dst])
                    {
                        visited[p.dest]=price;
                        q.emplace(price,p.dest);
                    }                    
                }
            }
        }
        return (visited[dst]==INT_MAX)?-1:visited[dst];           
    }
private:
    struct Flight
    {
        Flight(int d, int p):dest(d), price(p){}
        int dest;
        int price;
    };
    
};
