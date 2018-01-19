/*

Given a set of keywords words and a string S, make all appearances of all keywords in S bold.
Any letters between <b> and </b> tags become bold.

The returned string should use the least number of tags possible, and of course the tags should form a valid combination.

For example, given that words = ["ab", "bc"] and S = "aabcd", we should return "a<b>abc</b>d".
Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.

Note:

words has length in range [0, 50].
words[i] has length in range [1, 10].
S has length in range [0, 500].
All characters in words[i] and S are lowercase letters.

*/



class Solution {
public:
    string boldWords(vector<string>& dict, string s) {
        vector<pair<int, int>> ranges = findPairs(s, dict);
        
        ranges = merge (ranges);
        
        for (auto it = ranges.rbegin(); it != ranges.rend(); it++)
        {
            s.insert(it->second, "</b>");
            s.insert(it->first, "<b>");
        }
        return s;
    }
  
    vector<pair<int, int>> findPairs (string s, vector<string>& dict)
    {
        vector<pair<int, int>> res;
        for (auto str: dict)
        {
            int len = str.length();
            for (int i = 0; (i = s.find (str, i)) != string::npos; i++)
            {
                res.push_back(pair<int, int> (i, i + len));
            }
        }
        return res;
    }
  
    
    vector<pair<int, int>> merge (vector<pair<int, int>>& ranges)
    {
        vector< pair<int, int>> temp;
        sort(ranges.begin(), ranges.end(), compare);
        int j = -1;
        for (int i = 0; i < ranges.size(); i++) {
            if (j < 0 || ranges[i].first > temp[j].second)
            {
                temp.push_back(ranges[i]);
                j++;
            } else {
                temp[j].second = max (temp[j].second, ranges[i].second); 
            }
        }
        
        return temp;
    }
    
    
    
    
    static bool compare(pair<int, int>& a, pair<int, int>& b) {
        //This is amazing logic, make a note
        return a.first < b.first || a.first == b.first && a.second < b.second;
    }
    
};
