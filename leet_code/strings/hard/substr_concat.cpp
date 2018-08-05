/*

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting
indices of substring(s) in s that is a concatenation of each word in words exactly once 
and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/




//Related topics: Hash table, 2 pointers, String

//hash solution (very fast)
class Solution {
public:
   const uint64_t R = 1'000'000'007ull;
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = words.size();
        if (!n) return vector<int>();

        int m = words[0].size();

        vector<uint64_t> hash(m * n, 1);
        vector<uint64_t> chash(26, 0);
        mt19937 rng;

        generate(chash.begin(), chash.end(), rng);

        uint64_t target_hash = 1;
        for (auto &w : words) {
            uint64_t a = 0;
            uint64_t b = 0;
            if (w.size() != m) return vector<int>();
            for (auto &c : w) {
                a += chash[c-'a'];
                b += a;
            }
            target_hash *= b % R;
            target_hash %= R;
        }

        uint64_t a = 0;
        uint64_t b = 0;
        vector<int> ret;

        for (int i = 0; i < s.size(); ++i) {
            if (i >= m) {
                a -= chash[s[i-m]-'a'];
                b -= m * chash[s[i - m]-'a'];
            }
            a += chash[s[i]-'a'];
            b += a;

            if (i < m - 1) {
                continue;
            }
            
			auto total_hash = (b%R) * hash[(i + m*n-m) %(m*n)] % R;

            if (hash[i %(m*n)] * target_hash % R == total_hash) {
                ret.push_back(i + 1 - m * n);
            }
            
			hash[i %(m*n)] = total_hash;
        }

        return ret;
    }
};

//sliding window (next fastest)
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n=s.length(), cnt = words.size();
        vector<int> ans;
        if(n<=0||cnt<=0){
            return ans;
        }
        unordered_map<string, int> dict;
        for(int i=0;i<cnt;i++){
            dict[words[i]]++;
        }
        int wl = words[0].length();
        
        for(int i=0;i<wl;i++){
            unordered_map<string, int> t_dict;
            int count=0;
            int lft = i;
            for(int j=i;j<=n-wl;j+=wl){
                string str = s.substr(j, wl);
                // cout<<"str "<<str<<endl;
                if(dict.count(str)>0){
                    t_dict[str]++;
                    count++;                    
                    while(t_dict[str]>dict[str]){
                        // cout<<"in while"<<endl;                        
                        t_dict[s.substr(lft, wl)]--;                        
                        count--;
                        lft+=wl;
                        // cout<<"lft "<<lft<<endl;
                        // cout<<"count "<<count<<endl;
                        // cout<<"t_dict[str] "<<t_dict[str]<<endl;
                    }
                    // cout<<"//////";
                    if(count == cnt){
                        ans.push_back(lft);
                        t_dict[s.substr(lft, wl)]--;
                        lft+=wl;
                        count--;
                    }
                }
                else{
                    count=0;
                    t_dict.clear();
                    lft=j+wl;
                }
            }
        }
        return ans;
    }
};




//Very fast solution
class Solution {
public:
  unordered_map<string, pair<int,int> > dict;
  vector<string> nwords;
  vector<int> wordIndex;

  vector<int> findSubstring(string s, vector<string>& words) {
    int wordCount = 0;
    vector<int> sol;
    if (s.size() == 0 || words.size() == 0) {
        return sol;
    }
    for (int i = 0; i < words.size(); ++i) {
      if (dict.count(words[i])) 
        ++dict[words[i]].second;
      else {
        dict[words[i]] = make_pair(wordCount, 1);
        ++wordCount;
        nwords.push_back(words[i]);
      }
    }

    int L = words[0].size();
    int N = s.size();
    int M = words.size();

    wordIndex.resize(N, -1);

    for (int i = 0; i < N; ++i) if(i + L <= N) {
      string next = s.substr(i, L);
      wordIndex[i] = -1;
      if (dict.count(next))
        wordIndex[i] = dict[next].first;
    }

    
    vector<int> target(wordCount);
    for (int i = 0; i < wordCount; ++i) {
      target[i] = dict[nwords[i]].second;
    }
    
    for (int i = 0; i < L; ++i) {
      vector<int> mask(wordCount, 0);
      int onValue = 0;
      for (int j = 0; i + (j + 1)*L <= N; ++j) {
        int p = i + j * L;
        if (wordIndex[p] != -1) {
          ++mask[wordIndex[p]];
          if (mask[wordIndex[p]] == target[wordIndex[p]])
            ++onValue;
          else if (mask[wordIndex[p]] - 1 == target[wordIndex[p]])
            --onValue;
        }
        if (j >= M) {
          int pprev = p - M*L;
          if (wordIndex[pprev] != -1) {
            --mask[wordIndex[pprev]];
            if (mask[wordIndex[pprev]] == target[wordIndex[pprev]])
              ++onValue;
            else if (mask[wordIndex[pprev]] + 1 == target[wordIndex[pprev]])
              --onValue;
          }
        }

        if (onValue == wordCount)
          sol.push_back(i+(j-M+1)*L);
      }
    }

    return sol;
  }
};


//slowest of all
//2 map solution
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        vector<int> indexes;
        if (s.size() == 0 || words.size() == 0) {
            return indexes;
        }
    
        unordered_map<string, int> counts;
        /*
        Record the instances of each word
        */
        for (string word : words) {
            counts[word]++;
        }
        
        int n = s.length();
        int num = words.size();
        int len = words[0].length();
        int j = 0;
        
        for (int i = 0; i < (n - num * len + 1); i++) 
        {
            unordered_map<string, int> seen;
            for (j = 0; j < num; j++) 
            {
                /* 
                Get word by word
                */
                string word = s.substr(i + j * len, len);
                /* 
                If the word does not exist, then break
                */
                if (counts.find(word) == counts.end()) {
                    break;
                }
                seen[word]++;
                /*
                If the word is seen more than the expected instance, then break
                */
                if (seen[word] > counts[word]) {
                    break;
                }
            }
            /*
            If we successfully covered all the words
            then add the index
            */
            if (j == num) 
            {
                indexes.push_back(i);
            }
        }
        return indexes;
    }
};

