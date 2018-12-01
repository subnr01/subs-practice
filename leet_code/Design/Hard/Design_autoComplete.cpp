See leetcode for description




//Solution using hash and priority queue
class AutocompleteSystem {
public:
    map<string, int> M;
    string S;
    
    AutocompleteSystem(vector<string> sentences, vector<int> times) {
        int N = int(sentences.size());
        for (int i = 0; i < N; i++)
            M[sentences[i]] = times[i];        
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            ++M[S];
            S.clear();
            return vector<string>{};
        }

        S += c;

        priority_queue<pair<int, string>> Q; // to get 3 hotest strings
        if (!S.empty()) {
            auto t = S;
            ++t.back();

            // Just to create a while loop stop condition. It also can prevent iterating the whole M.
            auto it = M.lower_bound(S);
            auto itU = M.lower_bound(t);
            while (it != itU) {
                Q.emplace(-it->second, it->first);
                if (Q.size() > 3)
                    Q.pop();
                ++it;
            }
        }
        
        vector<string> res(Q.size());
        for (int i = int(Q.size()) - 1; i >= 0; i--) {
            res[i] = Q.top().second;
            Q.pop();
        }
        
        return res;      
    }
};

//Investigate TRIE solution
