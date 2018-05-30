/*

A password is considered strong if below conditions are all met:

It has at least 6 characters and at most 20 characters.
It must contain at least one lowercase letter, at least one uppercase letter, and at least one digit.
It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." is 
strong, assuming other conditions are met).
Write a function strongPasswordChecker(s), that takes a string s as input, and return the MINIMUM
change required to make s a strong password. If s is already strong, return 0.

Insertion, deletion or replace of any one character are all considered as one change.

*/

//Soln
class Solution {
public:
    int strongPasswordChecker(string s) {
        int n = s.size();
        int upper = 1, lower = 1, digit = 1;
        int toAdd = max(0, 6 - n);
        int toDel = max(0, n - 20);
        int rep = 0, add = 0, del = 0;
        // use to store consecutive letters based on len % 3
        // because lower value of len % 3 has precedence than
        // larger one on impact of reducing replacement number
        // len % 3 = 0, 1 deletion = 1 replacement aaa -> aa
        // len % 3 = 1, 2 deletion = 1 replacement aaaa -> aa
        // len % 3 = 2, 3 deletion = 1 replacement aaaaa -> aa
        // our goal is to use limited deletions to reduce
        // necessary replacement as many as possible
        vector<vector<int>> repeats(3);
        int j = 0;
        for (int i = 0; i <= n; i++) {
            if (i == n || s[i] != s[j]) {
                int len = i - j;
                if (i - j > 2) {
                    repeats[len % 3].push_back(len);
                }
                j = i;
            }
            if (i == n) break;
            if (isdigit(s[i])) digit = 0;
            if (isupper(s[i])) upper = 0;
            if (islower(s[i])) lower = 0;
        }

        for (int i = 0; i < 3; i++) {
            auto v = repeats[i];
            for (int j = 0; j < v.size(); j++) {
                if (i < 2) {
                    if (toAdd - add > 0) { // current length less than 6
                        add++;
                        v[j] -= i+1;
                    }
                    if (toDel - del > 0) { // current length larger than 20
                        del += i+1; // del could be larger than 'toDel' which will be made up below 
                        v[j] -= i+1;
                    }
                }
                rep += v[j] / 3;
            }
        }
        if (toDel - del > 0) {
            /* after v[j] -= i+1; in the for loop above, the length of all consecutive letters
            * handled by rep += v[j] / 3; meets len % 3 = 2, for example:
            * case len % 3 = 0 : "aaaaaa" => "aaaaa", rep get 1 credit via rep += v[j] / 3;
            * case len % 3 = 1 : "aaaaaaaaaa" => "aaaaaaaa", rep get 2 credits via rep += v[j] / 3;
            * now, there could be more letters to delete, i.e. toDel - del > 0
            * so, we need to take the credit given to rep back
            * because at the time rep got the credit, len % 3 is 2, to reduce 1 rep, we need to
            * do 3 deletions, that is how the number '3' comes out. 
            * certainly, if rep didn't get enough credits, we shouldn't overdraw, i.e. minimum rep
            * should be 0.
            */
            rep = max(0, rep - (toDel - del) / 3);
        }
        else {
            rep += del - toDel; // make up. del - toDel could only be 0 or 1
        }

        return toDel + max(toAdd + rep, upper + lower + digit);
    }
};

//Another soln
class Solution {
public:
    // I confess I did not understand the solution.
    int strongPasswordChecker(string s) {
        int deleteTarget = max(0, (int)s.length() - 20), addTarget = max(0, 6 - (int)s.length());
        int toDelete = 0, toAdd = 0, toReplace = 0, needUpper = 1, needLower = 1, needDigit = 1;
        
        for (int l = 0, r = 0; r < s.length(); r++) {
            if (isupper(s[r])) { needUpper = 0; }               
            if (islower(s[r])) { needLower = 0; }
            if (isdigit(s[r])) { needDigit = 0; }
            
            if (r - l == 2) {                               
                if (s[l] == s[l + 1] && s[l + 1] == s[r]) {     
                    if (toAdd < addTarget) { toAdd++, l = r; }  
                    else { toReplace++, l = r + 1; }           
                } else { l++; }                                 
            }
        }
        if (s.length() <= 20) { return max(addTarget + toReplace, needUpper + needLower + needDigit); }
        
        toReplace = 0;                                         
        vector<unordered_map<int, int>> lenCnts(3);            
        for (int l = 0, r = 0, len; r <= s.length(); r++) {    
            if (r == s.length() || s[l] != s[r]) {
                if ((len = r - l) > 2) { lenCnts[len % 3][len]++; } 
                l = r;
            }
        }
        
        for (int i = 0, numLetters, dec; i < 3; i++) {                
            for (auto it = lenCnts[i].begin(); it != lenCnts[i].end(); it++) {
                if (i < 2) {
                    numLetters = i + 1, dec = min(it->second, (deleteTarget - toDelete) / numLetters);
                    toDelete += dec * numLetters, it->second -= dec;                          
                    if (it->first - numLetters > 2) { lenCnts[2][it->first - numLetters] += dec; }   
                }
                toReplace += (it->second) * ((it->first) / 3);  
            }    
        }

        int dec = (deleteTarget - toDelete) / 3;                
        toReplace -= dec, toDelete -= dec * 3;
        return deleteTarget + max(toReplace, needUpper + needLower + needDigit);
    }
};

