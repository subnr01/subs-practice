/*

Validate if a given string is numeric.

Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true

*/


//faster Soln
class Solution {
public:
    bool isNumber(string s) {
        if (!s.size()) return false;
        while (*s.begin()==' ') s.erase(s.begin());
        while (*(s.end()-1)==' ') s.erase(s.end()-1);
        
        bool dotSeen = false;
        bool eSeen = false;
        bool numSeen = false;
        bool numSeenAfterE = false;
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]>='0' && s[i]<='9')
            {
                numSeen = true;
                numSeenAfterE = true;
            }
            else if (s[i]=='.')
            {
                if (dotSeen || eSeen) return false;
                dotSeen = true;
                // we do not require number after .
            }
            else if (s[i]=='e')
            {
                if (eSeen || !numSeen) return false;
                eSeen = true;
                numSeenAfterE = false;     // we need more number after e           
            }
            else if (s[i]=='-' || s[i]=='+')
            {
                if (i!=0 && s[i-1]!='e') return false;
                numSeen = false;            // we need number after -/+
                numSeenAfterE = false;
            }
            else
            {
                return false;
            }
        }
        
        return numSeen && numSeenAfterE; 
    }
};

class Solution {
public:
  
    bool isNumber(string s) 
{
    int i = 0;
    
    // skip the whilespaces
    for(; s[i] == ' '; i++) {}
    
    // check the significand
    if(s[i] == '+' || s[i] == '-') i++; // skip the sign if exist
    
    int n_nm, n_pt;
    for(n_nm=0, n_pt=0; (s[i]<='9' && s[i]>='0') || s[i]=='.'; i++)
        s[i] == '.' ? n_pt++:n_nm++;       
    if(n_pt>1 || n_nm<1) // no more than one point, at least one digit
        return false;
    
    // check the exponent if exist
    if(s[i] == 'e') {
        i++;
        if(s[i] == '+' || s[i] == '-') i++; // skip the sign
        
        int n_nm = 0;
        for(; s[i]>='0' && s[i]<='9'; i++, n_nm++) {}
        if(n_nm<1)
            return false;
    }
    
    // skip the trailing whitespaces
    for(; s[i] == ' '; i++) {}
    
    return i == s.size();  // must reach the ending 0 of the string
}
};


//DFA Soln
class Solution {
public:
    bool isNumber(string str) {
        int state=0, flag=0; // flag to judge the special case "."
        while(str[0]==' ')  str.erase(0,1);//delete the  prefix whitespace 
        while(str[str.length()-1]==' ') str.erase(str.length()-1, 1);//delete the suffix whitespace
        for(int i=0; i<str.length(); i++){
            if('0'<=str[i] && str[i]<='9'){
                flag=1;
                if(state<=2) state=2;
                else state=(state<=5)?5:7;
            }
            else if('+'==str[i] || '-'==str[i]){
                if(state==0 || state==3) state++;
                else return false;
            }
            else if('.'==str[i]){
                if(state<=2) state=6;
                else return false;
            }
            else if('e'==str[i]){
                if(flag&&(state==2 || state==6 || state==7)) state=3;
                else return false;
            }
            else return false;
        }
        return (state==2 || state==5 || (flag&&state==6) || state==7);
    }
};


