/*
We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)
* If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
* If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
* Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.

Example 1:
Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:
Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"

*/
class Solution {
private:
    bool isVowel(char c) {
        c = tolower(c);
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }
    
public:
    string toGoatLatin(string S) {
        string result;
        string append = "maa", w;
        istringstream line(S);
        while (line >> w) {
            if (!isVowel(w[0])) {
                w += w[0];         // Add the first charater to last
                w.erase(0, 1);     // Erase the first charater
            }
            w += append;           // Append maa, maaa, maaaa, ......
						
            result += w + " ";     // Add the word to result
            append += 'a';         // Prepare the next maaa, maaaa, maaaaa, ...
        }
        result.erase(result.size()-1, 1); // Don't forget to remove the whitespace at the end!
        return result;
    }
};
