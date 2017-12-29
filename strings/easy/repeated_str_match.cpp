/*
Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. 
If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".Return 3, because by repeating A three times (“abcdabcdabcd”),
B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

*/


//Check out how strings are declared
//https://stackoverflow.com/questions/8069092/c-string-declaration
class Solution {
public:
 
  /* 
  the logic is simple.
  Duplicate A q times and append until A.size() >= B.size();
  Then find whether B is a substr of A, otherwise duplicate
  and append one more time and return (q+1)
  */
 
 int repeatedStringMatch(string A, string B)
 {
    int q = 1;
    //string temp(A);
    //string temp(new string(A));
    /*
    does not work
    */
    // string temp = new string(A);
    string temp = A;
    
    for (; temp.size() < B.size(); q++) {
        temp.append(A);
    }
    if (temp.find(B) != std::string::npos) {
        return q;
    }
    temp.append(A);
    if (temp.find(B) != std::string::npos) {
        return q+1;
    }
    return -1;
 }

};
