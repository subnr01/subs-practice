/*
ZigZag Conversion
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of
rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:

string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

*/

//NOT A GOOD QUESTION

class Solution {
public:
    string convert(string s, int numRows) {
        if( numRows==1 ) return s;
        vector<string> res(numRows);
        int row=0;
        int increase=-1;
        for(int i=0; i<s.size(); ++i){
            
            // every time at turning point, we change the increase direction
            if (i%(numRows-1)==0) {
                increase *= -1;
            }
            
            res[row].push_back(s[i]);
            row += increase;
        }
        
        string ret;
        for(const auto& str:res){
            ret += str;
        }
        
        return ret;
    }
};
