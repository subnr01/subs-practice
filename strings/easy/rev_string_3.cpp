/*

Reverse k positions for every 2k in a string.
If k > size(), then reverse the entire left over length.
*/



class Solution {
public:
    string reverseStr(string s, int k) {
    for (int i = 0; i < s.size(); i+=2*k) {
        if(i + k < s.size()) {
            reverse(s.begin() + i, s.begin()+i+k);
        } else {
            reverse(s.begin() + i, s.end());
        }
    }
    return s;

}
};
