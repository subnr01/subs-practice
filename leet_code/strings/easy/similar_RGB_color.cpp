/*
In the following, every capital letter represents some hexadecimal digit from 0 to f.

The red-green-blue color "#AABBCC" can be written as "#ABC" in shorthand.  For example, "#15c" is 
shorthand for the color "#1155cc".

Now, say the similarity between two colors "#ABCDEF" and "#UVWXYZ" is -(AB - UV)^2 - (CD - WX)^2 - (EF - YZ)^2.

Given the color "#ABCDEF", return a 7 character color that is most similar to #ABCDEF, and has a shorthand 
(that is, it can be represented as some "#XYZ"

Example 1:
Input: color = "#09f166"
Output: "#11ee66"
Explanation:  
The similarity is -(0x09 - 0x11)^2 -(0xf1 - 0xee)^2 - (0x66 - 0x66)^2 = -64 -9 -0 = -73.
This is the highest among any shorthand color.


*/

class Solution {
public:
    string helper(string str) 
    {
    string dec_to_hex = "0123456789abcdef", res = "";

    int dec_num = stoi(str, nullptr, 16);
    int q = dec_num / 17;
    if ((dec_num % 17) > 8) q = q + 1;
    res = res + dec_to_hex[q] + dec_to_hex[q];
    return res;
   }

string similarRGB(string color) {
    return "#" + helper(color.substr(1, 2)) + helper(color.substr(3, 2)) + helper(color.substr(5, 2));
}
