ToLower case
Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.
 
Example 1:
Input: "Hello"
Output: "hello"

string toLowerCase(string str) {
        for(char& c: str)
            if('A'<= c && c<='Z') {
                c = c-'A'+'a';
            }
        return str;
}
