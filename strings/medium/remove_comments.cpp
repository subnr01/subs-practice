/*

 Remove Comments
 
 
 Too long to paste here.
 */



class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> ans;
        string s;
        bool comment = false;
     
        for(int i = 0; i < source.size(); i++) {
            for(int j = 0; j < source[i].size(); j++) {
                 //If comment not set to true and the first two characters are //, then break and go
                 // to the next line
                if(!comment && 
                   j + 1 < source[i].size() && source[i][j] == '/' && source[i][j+1]=='/') {
                 break;
                }
                
                //if comment is not set to true and it looks like beginning of a comment, then set comment
                //to true and parse the string continuously.
                else if(!comment && 
                        j + 1 < source[i].size() && source[i][j] == '/' && source[i][j+1]=='*') {
                 comment = true; 
                 j++;
                }
                // if comment is set to true and we are at the end of a comment, then set it to false.
                else if(comment &&
                        j + 1 < source[i].size() && source[i][j] == '*' && source[i][j+1]=='/') {
                 comment = false; 
                 j++;
                }
                //If it is not a comment, then push the string.
                else if(!comment) {
                 s.push_back(source[i][j]);
                }
            }
            // if it is not a comment and we reached size of the string, then push it 
            // into the vector.
            if(!comment && s.size()) {
             ans.push_back(s); 
             s.clear();
            }
        }
        return ans;
    }
};
