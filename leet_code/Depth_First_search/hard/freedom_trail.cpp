/*
Refer leetcode
*/

//Related topics: DP, DFS but seems DP is popular.

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        vector<int> pos[26];
        for (int i = 0; i < ring.size(); ++i) {
            pos[ring[i]-'a'].push_back(i);
        }
        int init = 0, n = ring.size();
        vector<int> run(n, 0);
        for (int i = key.size()-1; i > 0; --i) {
            vector<int> nrun(n, INT_MAX);
            for (auto& p : pos[key[i-1]-'a']) {
                for (auto& q : pos[key[i]-'a']) {
                    nrun[p] = min(nrun[p], run[q]+min(abs(p-q), n-abs(p-q)));
                }
            }
            swap(run, nrun);
        }
        int res = INT_MAX;
        for (auto& p : pos[key[0]-'a']) {
            res = min(res, run[p]+min(p, n-p));
        }
        return res + key.size();
    }
};



//DFS soln
public class Solution {
    public int findRotateSteps(String ring, String key) {
           Map<String,Integer> map = new HashMap();
           return dfs(ring, key, 0, map);
    }
    
    public int dfs(String ring, String key, int index, Map<String,Integer> map){
        if(index == key.length()){
            return 0;
        }
    
        char c = key.charAt(index);
        String hashKey = ring + index;
        if(map.containsKey(hashKey)) return map.get(hashKey);
        
        int minSteps = Integer.MAX_VALUE;
        for(int i = 0; i < ring.length(); i ++){
            if(ring.charAt(i) == c){
                String s = ring.substring(i, ring.length()) + ring.substring(0, i);
                int steps = 1 + Math.min(i, ring.length() - i);
                steps += dfs(s, key, index + 1, map);
                minSteps = Math.min(minSteps, steps);
            }
        }
        
        map.put(hashKey, minSteps);
        
        return minSteps;
    }
}



