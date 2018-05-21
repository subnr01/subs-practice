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
    string convert(string s, int nRows) {
    
    if (nRows <= 1)
        return s;

    const int len = (int)s.length();
    vector<string> str(nRows);
        
    int row = 0, step = 1;
    for (int i = 0; i < len; ++i)
    {
        //CRUX of the logic is
        //here. It all matters how
        // you insert the element
        // into the vector.
        // it is about inserting the elements in
        // this order of rows:
        // 0, 1, 2, 1, 0, 1, 2, 1, 0 and so on
        str[row].push_back(s[i]);

        if (row == 0)
            step = 1;
        else if (row == nRows - 1)
            step = -1;

        row += step;
    }

    s.clear();
    for (int j = 0; j < nRows; ++j)
    {
        //ANOTHER IMPORTANT OBSERVATION EASY TO MISS
        // WE ARE APPENDING ROWS here and not single
        // characters, so ...
        s.append(str[j]);
    }

    return s;
  }
};
