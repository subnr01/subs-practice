/*
Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. 
Find and return the shortest palindrome you can find by performing this transformation.

For example:

Given "aacecaaa", return "aaacecaaa".

Given "abcd", return "dcbabcd".

*/

//There is a KMP soln available as well, which can be looked at later.



//Simple answer
string shortestPalindrome(string s)
    {
        int n = s.size();
        if(n == 0) return s;
        
        int i = n;
        string v = s; 
        reverse(v.begin(), v.end());  //Reverse s.
        
        for(; i >= 1; --i)
        {
            if(s.substr(0, i) == v.substr(n - i)) break;    //palindrome?
        }
        for(; i < s.size(); i += 2) s = s[i] + s;   //Construct
        return s;
    }
    
    
    //Non recursive soln
    class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.length();
        int leftMost=0;
        int rightMost=0;
        int i=0, start, end;
        while(i<n)
        {
            start = i;
            while(s[i]==s[start])
            {
                i++;
            }
            end = i-1;
            while(start-1>=0 && end+1<n && s[start-1]==s[end+1])
            {
                start--;
                end++;
            }
            if(start==0 && (end-start) > (rightMost-leftMost))
            {
                leftMost = 0;
                rightMost = end;
            }
        }
        
        string result;
        if(rightMost<n-1)
        {
            result = s.substr(rightMost+1, n-rightMost);
            reverse(result.begin(), result.end());
        }
        result = result + s;
        
        return result;
    }
};


//2 Pointers and recursion
string shortestPalindrome(string s)
{
    int n = s.size();
    int i = 0;
    for (int j = n - 1; j >= 0; j--) {
        if (s[i] == s[j])
            i++;
    }
    if (i == n)
        return s;
    string remain_rev = s.substr(i, n);
    reverse(remain_rev.begin(), remain_rev.end());
    return remain_rev + shortestPalindrome(s.substr(0, i)) + s.substr(i);
}
