class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) 
    {
        vector<bool> res;
        
        for (auto query : queries)
        {
           res.push_back(doesMatch(query, pattern));
        }
        return res;
    }
    
    bool doesMatch (string query, string pattern)
    {
        int i = 0;
        for (auto c : query)
        {
            if (i < pattern.size() && c == pattern[i]) {
                i++;
            } 
            else if (c < 'a') {
                return false;
            }
        }
        return i == pattern.size();
    }
};
