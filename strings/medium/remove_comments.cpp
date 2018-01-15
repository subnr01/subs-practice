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
            //SEE J IS COMPARED TO source[i].size()
            for(int j = 0; j < source[i].size(); j++) {
              
                 //SEE J IS COMPARED TO source[i].size()
                if(!comment && 
                   j + 1 < source[i].size() && source[i][j] == '/' && source[i][j+1]=='/') {
                 break;
                }
   
                //SEE J IS COMPARED TO source[i].size()
                else if(!comment && 
                        j + 1 < source[i].size() && source[i][j] == '/' && source[i][j+1]=='*') {
                 comment = true; 
                 j++;
                }

                //SEE J IS COMPARED TO source[i].size()
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
    
            //String size is also compared
            if(!comment && s.size()) {
             ans.push_back(s); 
             s.clear();
            }
        }
        return ans;
    }
};
