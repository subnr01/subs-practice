/*
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

*/



class Solution {
public:
    void reverseWords(string &s) {
       
        //reverse the entire string
        reverse (s.begin(), s.end());
        
        int n = s.size();
        int storeindex = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] != ' ')
            {
               //word boundary
                if (storeindex != 0) {
                    s[storeindex++] = ' ';
                }
                int j = i;
                while ( j < n && s[j] != ' ') 
                {
                    s[storeindex++] = s[j++];
                }
                //begin to end of the word, begin to the beginning of the word
                // WE CANNOT USE JUST I HERE, BECAUSE THE REVERSE MUST HAPPEN
                // ON THE CHANGED STRING WHICH IS INDEXED BY STOREINDEX, BUT 
                // STOREINDEX HAS CHANGED TO END OF THE WORD, SO TO MAKE IT
                // COME TO THE BEINGNING OF THE WORD, WE HAVE TO SUBSTRACT THE
                // WORD SIZE . (j-i)
                reverse (s.begin() + storeindex - (j-i), s.begin() + storeindex);
                
                i = j;
            }
            
            //Delete space from storeindex to end of the string
            // so as to compress the string at the end and get rid of
            //spaces
            s.erase (s.begin() + storeindex, s.end());
            
        }
        
    }
};
