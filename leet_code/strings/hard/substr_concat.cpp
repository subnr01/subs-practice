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



//2 map solution
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> counts;
        for (string word : words)
            counts[word]++;
        int n = s.length(), num = words.size(), len = words[0].length();
        vector<int> indexes;
        for (int i = 0; i < n - num * len + 1; i++) {
            unordered_map<string, int> seen;
            int j = 0;
            for (; j < num; j++) {
                string word = s.substr(i + j * len, len);
                if (counts.find(word) != counts.end()) {
                    seen[word]++;
                    if (seen[word] > counts[word])
                        break;
                } 
                else break;
            }
            if (j == num) indexes.push_back(i);
        }
        return indexes;
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

