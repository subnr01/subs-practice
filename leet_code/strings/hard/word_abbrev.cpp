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



