/*

Given an array of n distinct non-empty strings, you need to generate minimal possible abbreviations 
for every word following rules below.

Begin with the first character and then the number of characters abbreviated, which followed by the last character.
If there are any conflict, that is more than one words share the same abbreviation, a longer prefix is used instead 
of only the first character until making the map from word to abbreviation become unique. In other words, a 
final abbreviation cannot map to more than one original words.


If the abbreviation doesn't make the word shorter, then keep it as original.
Example:
Input: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
Note:
Both n and the length of each word will not exceed 400.
The length of each word is greater than 1.
The words consist of lowercase English letters only.
The return answers should be in the same order as the original array.


*/

//Related topics: String, sort




//shorter soln
class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        int n = dict.size();
        unordered_map<string, int> count;
        vector<int> len(n, 1);
        vector<string> res(n);
        
        for (int i = 0; i < dict.size(); ++i) {
            res[i] = abbr(dict[i], len[i]);
            count[res[i]]++;
        }
        
        while (1) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (count[res[i]] > 1) {
                    len[i]++;
                    res[i] = abbr(dict[i], len[i]);
                    count[res[i]]++;
                    cnt++;
                }
            }
            if (!cnt) break;
        }
        
        return res;
    }
private:
    string abbr(string s, int i) {
        if (i + 2 >= s.size()) return s;
        else {
            return s.substr(0, i) + to_string(s.size() - i - 1) + s.back();
        }
    }
};

//prefix soln
class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        /* Detailed implementation Time O(wordLen * N^2)  space O(N)*/
        vector<string> output;
        int n = dict.size();
        vector<int> prefixLen(n, 1);
        vector<int> conflicts;
        
        // 1. initialize the abbrs with prefix length of 1
        for (int i = 0; i < n; ++i) {
            output.push_back(getKey(dict[i], prefixLen[i]));
        }
        
        // 2. resolve conflicts
        for (int i = 0; i < n; ++i) {
            
            // resolve conflicts with i and the words after it
            while (true) {    
                for (int j = i + 1; j < n; ++j) {
                    if (output[i] == output[j]) {  // conflict detected
                        conflicts.push_back(j);
                    }
                }
                
                if (conflicts.empty()) break;
                conflicts.push_back(i); // Add the element itself to grow with other words
                for (int p : conflicts) {
                    ++prefixLen[p];
                    output[p] = getKey(dict[p], prefixLen[p]);
                }
                
                conflicts.clear();
            }
        }
        
        return output;
        
    }
    
    // Use the first k chars as prefix
    string getKey(string str, int k) {
        if (k >= str.size() - 2) return str;
        return str.substr(0, k) + to_string(str.size() - k - 1) + str.back();
    }
};

/***************************************************************************************************/
//VERY FAST SOLN
// a.size( ) == b.size( )
// first and last character
// the remaining characters
// After sorting, we only need compare a certain word to its previous and next word for longest common prefix, in order to decide its abbreviation.
// n is the size of dict, and m is the average length of word in dict. Sorting complexity is O(mnlogn), and the procedure after sorting is O(mn).
class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        int n = dict.size();
        vector<string> ans = dict;
        // sort the dict
        sort(dict.begin(), dict.end(), mycompare);
        unordered_map<string, string> mp;
        // prefix is the longest common prefix between dict[i] and dict[i-1]
        int prefix = 0; 
        for (int i = 0; i < n; ++i) {
            int j = 0;
            // j is the longest prefix length between dict[i] and dict[i+1]
           // if dict[i] is last word, or the length is different, or the last character is different, j = 0;
            if (i < n-1 && dict[i].size() == dict[i+1].size() && dict[i].back() == dict[i+1].back()) {
                while (j < dict[i].size() && dict[i][j] == dict[i+1][j]) //找到第一个不同的
                    j++;
            }
            if (j > prefix) prefix = j; // prefix是上一个的残留，如果为0，就是不一样长的， 如果不为零，说明这两个一样长，需要至少prefix个中间
            // build abbreviation if it is shorter than word, and put it in a map
            if (dict[i].size() > prefix+3) { //头尾 多一个
                string s = dict[i].substr(0, prefix+1)+to_string(dict[i].size()-prefix-2)+dict[i].back();
                mp[dict[i]] = s;
            }
            // update prefix to be longest prefix with previous word
            prefix = j;
        }
        for (int i = 0; i < n; ++i) {
            if (mp.count(ans[i])) ans[i] = mp[ans[i]];
        }
        return ans;
    }
private:
    static bool mycompare(string& a, string& b) {
        if (a.size() == b.size()) {
            if (a.back() < b.back()) 
                return true;
            else if (a.back() > b.back()) 
                return false;
            for (int i = 0; i < a.size()-1; ++i) {
                if (a[i] < b[i]) 
                    return true;
                else if (a[i] > b[i])
                    return false;
            }
        }
        return a.size() < b.size(); //（mnlog（N））
    }
};
/***************************************************************************************************/
class Solution {
public:
  vector<string> wordsAbbreviation(vector<string>& dict) {
    vector<string> result(dict.size());
    unordered_map<string, vector<int>> map;
    
    for(int i=0; i<dict.size(); i++) {
      if(dict[i].size() <= 3)
        result[i] = dict[i];
      else {
        string key = encode(dict[i], 1);
        map[key].push_back(i);
      }
    }
    
    for(auto p : map) {
      if(p.second.size() == 1)
        result[p.second.front()] = p.first;
      else
        helper(dict, p.second, 1, result);
    }
    return result;
  }
  
  void helper(vector<string> &dict, vector<int> & lt, int index, vector<string> &result) {
    if(lt.size() == 1) {
      result[lt.front()] = encode(dict[lt.front()], index);
      return;
    }
    
    int maxNumSame = 0, numDistinct = 0;
    vector<int> stat(26, 0);
    for(int i=0; i<lt.size(); i++) {
      int idx = dict[lt[i]][index] - 'a';
      if(stat[idx] == 0) numDistinct++;
      maxNumSame = max(maxNumSame, ++stat[idx]);
    }
    if(maxNumSame == lt.size()) { // all the same
      helper(dict, lt, index+1, result);
    }
    else if(numDistinct == lt.size()) { // all different
      for(auto n : lt)
        result[n] = encode(dict[n], index+1);
    }
    else {
      vector<vector<int>> vv(26, vector<int>());
      for(auto n : lt)
        vv[dict[n][index]-'a'].push_back(n);
      
      for(auto v : vv)
        if(!v.empty())
          helper(dict, v, index+1, result);
    }
  }
  
  string encode(string s, int start) {
    int len = s.length() - start - 1;
    if(len > 1)
      return s.substr(0, start) + to_string(len) + s.back();
    else
      return s; 
  }
};



