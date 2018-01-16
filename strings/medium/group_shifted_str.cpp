/*
Given a string, we can "shift" each of its letter to its successive letter, 
for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence: "abc" -> "bcd" -> ... -> "xyz".

Given a list of strings which contains only lowercase alphabets, group all strings 
that belong to the same shifting sequence, return:

 [
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]

*/

//https://www.programcreek.com/2014/05/leetcode-group-shifted-strings-java/

//https://discuss.leetcode.com/topic/20823/4ms-easy-c-solution-with-explanations


class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string> > mp;
        for (string  s : strings)
            mp[shift(s)].push_back(s);
        vector<vector<string> > groups;
        for (auto m : mp) {
            vector<string> group = m.second;
            sort(group.begin(), group.end());
            groups.push_back(group);
        }
        return groups;
    }
private:
    string shift(string& s) {
        string t;
        int n = s.length();
        for (int i = 1; i < n; i++) {
            int diff = s[i] - s[i - 1];
            if (diff < 0) diff += 26;
            t += 'a' + diff + ',';
        }
        return t;
    }
};


//Another soln
vector<vector<string>> groupStrings(vector<string>& strings) {
	unordered_map<string, vector<string>> hmap;

	for (int i = 0; i<strings.size(); i++) {
		string t = strings[i];
		int diff = t[0] - 'a';
		for (int j = 0; j<strings[i].size(); j++) {
			if (t[j] - diff - 'a' >= 0)
				t[j] = t[j] - diff;
			else 
				t[j] = (t[j] - diff) + 26;
		}

		hmap[t].push_back(strings[i]);
	}

	vector<vector<string>> result;
	for (auto iter = hmap.begin(); iter != hmap.end(); ++iter) {
		result.push_back(iter->second);
		sort(result.back().begin(), result.back().end());
	}

	return result;
}
