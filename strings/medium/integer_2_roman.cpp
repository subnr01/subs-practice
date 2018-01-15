/*
12. Integer to Roman


Given an integer, convert it to a roman numeral.

Input is guaranteed to be within the range from 1 to 3999.

*/



class Solution {
    
public:
    
  //Array of pairs
    vector<pair<string, int>>arr=
    { make_pair("M",1000),
      make_pair("CM", 900),
      make_pair("D", 500),
      make_pair("CD", 400),
      make_pair("C", 100),
      make_pair("XC", 90),
      make_pair("L", 50),
      make_pair("XL", 40),
      make_pair("X", 10),
      make_pair("IX", 9),
      make_pair("V", 5),
      make_pair("IV", 4),
      make_pair("I", 1) 
    };
      
      
    string intToRoman(int num) {
        string res;
        int i = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            //num is greater than or equal to         
            while(num >= arr[i].second) {
                res.append(arr[i].first);
                num -= arr[i].second;
            } 
        }
        
        return res;
        
    }
};

