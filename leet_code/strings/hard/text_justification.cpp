/*
Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left 
and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad 
extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do 
not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted 
between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

*/
class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L) {
    vector<string> res;
    for(int i = 0, k, l; i < words.size(); i += k) {
        for(k = l = 0; i + k < words.size() and l + words[i+k].size() <= L - k; k++) {
            l += words[i+k].size();
        }
        string tmp = words[i];
        for(int j = 0; j < k - 1; j++) {
            if(i + k >= words.size()) tmp += " ";
            else tmp += string((L - l) / (k - 1) + (j < (L - l) % (k - 1)), ' ');
            tmp += words[i+j+1];
        }
        tmp += string(L - tmp.size(), ' ');
        res.push_back(tmp);
    }
    return res;
}
};


//faster soln
class Solution {
public:
    string get_space(int num) {
        string now;
        while (num--) {
            now += ' ';
        }
        return now;
    }
    
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        if (words.size() == 0) return ans;
        
        int i = 0, j = 0, k;
        while (i < words.size()) {
            int now = words[i].size();
            for (j = i + 1; j < words.size(); j++) {
                if (now + 1 + words[j].size() > maxWidth)
                    break;
                now = now + 1 + words[j].size();
            }
            int space = 0, extra = 0;
            string res;
            
            if (j == i + 1 || j == words.size()) {
                res = words[i];
                for (k = i + 1; k < j; k++) {
                    res = res + " " + words[k];
                }
                space = maxWidth - now;
                res += get_space(space);
            } else {
                int spaceSlot = j - i - 1;
                space = (maxWidth - now) / spaceSlot + 1;
                extra = (maxWidth - now) % spaceSlot;
                
                for (k = i; k < j - 1; k++) {
                    res += words[k];
                    res += get_space(space);
                    if (extra > 0) {
                        res += ' ';
                        extra--;
                    }
                }
                
                res += words[k];
            }
            i = j;
            ans.push_back(res);
        }
        return ans;
    }
};
