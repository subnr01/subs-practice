/*

Given two strings S and T, determine if they are both one edit distance apart.

An edit between two strings is one of the following changes.

Add a character
Delete a character
Change a character
Given two string s1 and s2, find if s1 can be converted to s2 with exactly one edit. Expected time complexity is
O(m+n) where m and n are lengths of two strings.

*/


/* 
Solution:
Let the input strings be s1 and s2 and lengths of input 
strings be m and n respectively.

1) If difference between m an n is more than 1, 
     return false.
2) Initialize count of edits as 0.
3) Start traversing both strings from first character.
    a) If current characters don't match, then
       (i)   Increment count of edits
       (ii)  If count becomes more than 1, return false
       (iii) If length of one string is more, then only
             possible  edit is to remove a character.
             Therefore, move ahead in larger string.
       (iv)  If length is same, then only possible edit
             is to  change a character. Therefore, move
             ahead in both strings. 
    b) Else, move ahead in both strings. 
    
*/



//Simple solution (programm creek)
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
	int len1 = s.size();
	int len2 = t.size();

	if ( abs(len1 - len2) > 1) {
		return false;
	}

	int i = 0;
	int j = 0;
	int count = 0;


	while ( i<len1 && j<len2)
	{
		if (s[i] == t[j]) {
			++i;
			++j;
		} else {
			count++;
			if (count > 1) {
				return false;
			}

			if (len1 > len2) {
				++i;
            }
			else if (len2 > len1) {
				++j;
			} else {
			/*
			Do not forget to do this part
			*/
			    ++i;
			    ++j;
            }
		}
	}

	if(i<len1 || j<len2){
		count++;
	}

	return count == 1;

}

};


// Slightly difficult solution.
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.length(), n = t.length();
        if (m > n) return isOneEditDistance(t, s);
        if (n - m > 1) return false;
        bool mismatch = false;
        for (int i = 0; i < m; i++) {
            if (s[i] != t[i]) {
                if (m == n) s[i] = t[i];
                else s.insert(i, 1, t[i]);
                mismatch = true; 
                break;
            }
        }
        return (!mismatch && n - m == 1) || (mismatch && s == t);
    }
};
