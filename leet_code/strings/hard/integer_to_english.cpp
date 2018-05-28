/*

Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 2^31 - 1.

For example,
123 -> "One Hundred Twenty Three"
12345 -> "Twelve Thousand Three Hundred Forty Five"
1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
Show Hint 


*/


//Java
//convert this to c++, looks well written

private final String[] LESS_THAN_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
private final String[] TENS = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
private final String[] THOUSANDS = {"", "Thousand", "Million", "Billion"};

public String numberToWords(int num) {
    if (num == 0) return "Zero";

    int i = 0;
    String words = "";
    
    while (num > 0) {
        if (num % 1000 != 0)
    	    words = helper(num % 1000) +THOUSANDS[i] + " " + words;
    	num /= 1000;
    	i++;
    }
    
    return words.trim();
}

private String helper(int num) {
    if (num == 0)
        return "";
    else if (num < 20)
        return LESS_THAN_20[num] + " ";
    else if (num < 100)
        return TENS[num / 10] + " " + helper(num % 10);
    else
        return LESS_THAN_20[num / 100] + " Hundred " + helper(num % 100);
}


//Using Map

classclass  SolutionSolution { {
 publicpublic:
    
    
    :               // Easy to understand solution 1:// Easy to understand  
    // https://leetcode.com/problems/integer-to-english-words/discuss/70651/Fairly-Clear-4ms-C++-solution
    
    // The Optimal solution:
    // https://leetcode.com/problems/integer-to-english-words/discuss/70625/My-clean-Java-solution-very-easy-to-understand
    
    
    unordered_map<int, string> wordMap = {
        { 0, "Zero"       },
        { 1, "One"        },
        { 2, "Two"        },
        { 3, "Three"      },
        { 4, "Four"       },
        { 5, "Five"       },
        { 6, "Six"        },
        { 7, "Seven"      },
        { 8, "Eight"      },
        { 9, "Nine"       },
        { 10, "Ten"       },
        { 11, "Eleven"    },
        { 12, "Twelve"    },
        { 13, "Thirteen"  },
        { 14, "Fourteen"  },
        { 15, "Fifteen"   },
        { 16, "Sixteen"   },
        { 17, "Seventeen" },
        { 18, "Eighteen"  },
        { 19, "Nineteen"  },
        { 20, "Twenty"    },
        { 30, "Thirty"    },
        { 40, "Forty"     },
        { 50, "Fifty"     },
        { 60, "Sixty"     },
        { 70, "Seventy"   },
        { 80, "Eighty"    },
        { 90, "Ninety"    }
    };
    
    unordered_map<int, string> THOUSNAD = {
        { 1, "Thousand" },
        { 2, "Million"  },
        { 3, "Billion"  }
    };
    
    string numberToWords(int num) {
        string words;
        
        if(num == 0)    return wordMap[num];
        
        int i = 0;
        while(num) {
            int reminder = num % 1000;
            
            // e.g. 1,000,000
            if(reminder > 0) {
                words = toWords(reminder) + (i > 0 ? " " + THOUSNAD[i] + " " + words : "");
            }
            
            i ++;
            num /= 1000;
        }
        
        // Care: clean up the trailing space, e.g. 1000
        if(words[words.size() - 1] == ' ') {
            words.pop_back();
        }
        
        return words;
    }
    
private:
    // Translates n (n < 100) to words
    string toWords(int n) {
        string words;
       
        if(n >= 100) {
            words += wordMap[n/100] + " Hundred ";
            n %= 100;
        }
        
        if(n >= 20) {
            words += wordMap[n/10 * 10] + " ";
            n %= 10;
        }
        
        // Care n > 0 here! e.g. 20
        if(n > 0 & n < 20) {
            words += wordMap[n];
        }
        
        // Care: clean up the trailing space, e.g. 100
        if(words[words.size() - 1] == ' ') {
            words.pop_back();
        }
        
        return words;
    }
};
                              
                              
