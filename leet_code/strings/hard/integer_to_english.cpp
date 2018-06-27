/*

Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 2^31 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Show Hint 


*/


//C++

class Solution {
    vector<string> LESS_THAN_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", 
                                   "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                                   "Eighteen", "Nineteen"};
    
    vector<string> TENS = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    
    vector<string> THOUSANDS = {"", "Thousand", "Million", "Billion"};
public:
    string numberToWords(int n)
    {
        if (n == 0)
        {
            return "Zero";
        }
        
        int i = 0;
        string words = "";
        
        while (n > 0)
        {
            if (n % 1000 != 0)
            {
                words = helper(n % 1000) + THOUSANDS[i] + " " + words;
            }
            n = n / 1000;
            i++;
        }
        
        //This may not be the most effecient implementation
        while (isspace(words[words.size() - 1])) {
            words.erase(words.size()-1);
        }
        return words;
        
    }
    
    string helper (int num)
    {
        if (num == 0) {
            //This is important, otherwise we will
            // get extra space after TEN
            return "";
        }
        else if (num < 20)
        {
            return LESS_THAN_20[num] + " ";
        }
        else if (num < 100)
        {
            return TENS[num / 10] + " " + helper(num % 10);
        } else {
            return LESS_THAN_20[num / 100] + " Hundred " + helper(num % 100);
        }
    }
};


