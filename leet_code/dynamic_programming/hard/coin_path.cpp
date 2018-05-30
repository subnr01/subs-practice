/*

refer leetcpde
*/

class Solution {
public:
    vector<int> cheapestJump(vector<int>& A, int B) {
        vector<int> ans;
        if (A.empty() || A.back() == -1) return ans;
        int n = A.size();
        vector<int> dp(n, INT_MAX), pos(n, -1);
        dp[n-1] = A[n-1];
        // working backward
        for (int i = n-2; i >= 0; i--) {
            if (A[i] == -1) continue;
            for (int j = i+1; j <= min(i+B, n-1); j++) {
                if (dp[j] == INT_MAX) continue;
                if (A[i]+dp[j] < dp[i]) {
                    dp[i] = A[i]+dp[j];
                    pos[i] = j;
                }
            }
        }
        // cannot jump to An
        if (dp[0] == INT_MAX) return ans;
        int k = 0;
        while (k != -1) {
            ans.push_back(k+1);
            k = pos[k];
        }
        return ans;
    }
};

//with memoisaton
class Solution {
public:

    vector<int> cheapestJump(vector<int>& A, int B)
    {
        unordered_map<int, int> cache;
        int n = A.size();
        vector<int> parents (n, -1);
        cheapestJumpInternal(A, B, 0, &parents, &cache);
        
        vector<int> cheapest;
        
        for (int i = 0; i < n && i != -1; i = parents[i])
            cheapest.push_back(i + 1);
        
        if (!cheapest.empty() && cheapest.back() != n)
            cheapest.clear();

        return cheapest;
    }
    
    int cheapestJumpInternal(const vector<int>& A, int B, int pos, vector<int>* pParents, unordered_map<int, int>* pCache)
    {
        const int c_MaxVal = 101 * 1000; // numeric_limits<int>::max();
        unordered_map<int, int>& cache = *pCache;
        vector<int>& parents = *pParents;
        int n = A.size();

        if (A[pos] == -1)
            return c_MaxVal;        
        
        if (pos == n - 1)
            return A[n - 1];
        
        if (cache.find(pos) == cache.end())
        {
            int cheapestCost = c_MaxVal;
            
            for (int i = 1; i <= B && pos + i < n; i++)
            {
                int neigh = pos + i;
                
                if (A[neigh] == -1)
                    continue;
                
                int cost = A[pos] + cheapestJumpInternal(A, B, neigh, pParents, pCache);
                     
                if (cost < cheapestCost)
                {
                    parents[pos] = neigh;
                    cheapestCost = cost;
                }
            }
            
            cache[pos] = cheapestCost;
        }
        
        return cache[pos];
    }
};
