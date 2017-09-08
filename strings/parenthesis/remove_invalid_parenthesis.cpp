/*

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]

*/


// Solution 1
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        /*** count-the-needed-to-delete-number ***/
        int left=0, right=0;
        for(int i=0; i<s.size(); i++){
            if(s[i]=='(') left++;
            else if(s[i]==')'){
                if(left>0) left--;
                else right++;
            }
        }
        
        unordered_set<string> result;
        help(result, "", s, 0, 0, left, right);
        return vector<string>(result.begin(), result.end());
    }
    
    void help(unordered_set<string> &result, string cur, string s, int pos, int pair, int left, int right){
        if(pos==s.size()){
            if(pair==0 && left==0 && right==0)  result.insert(cur);
            return;
        }
        if(s[pos]=='('){
            /*** skip ***/
            if(left>0){
                help(result, cur, s, pos+1, pair, left-1, right);
            }
            /*** keep ***/
            help(result, cur+'(', s, pos+1, pair+1, left, right);
        }
        else if(s[pos]==')'){
            /*** skip ***/
            if(right>0){
                help(result, cur, s, pos+1, pair, left, right-1);
            }
            /*** keep ***/
            /*** bug-places : I forget to check whether pair > 0 ***/
            if(pair>0){
                help(result, cur+')', s, pos+1, pair-1, left, right);
            }
        }
        else{
            help(result, cur+s[pos], s, pos+1, pair, left, right);
        }
    }
};



//Solution 2
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        if(s==""){
            result.push_back(s);
            return result;
        } 
        /*** use the visited to record the visited string ***/
        unordered_set<string> visited;
        /*** use the deque to do the BFS ***/
        deque<string> queue;
        queue.push_back(s);
        visited.insert(s);
        bool found=false;
        while(!queue.empty()){
            string temp=queue.front();
            queue.pop_front();
            if(check(temp)){
                result.push_back(temp);
                found=true;
            }
            /*** if found, stop to increase the level depth ***/
            if(found)  continue;
            for(int i=0; i<temp.size(); i++){
                if(temp[i]!='(' && temp[i]!=')') continue;
                string str=temp.substr(0, i)+temp.substr(i+1);
                if(visited.find(str)==visited.end()){
                    queue.push_back(str);
                    visited.insert(str);
                }
            }
        }
        return result;
    }
    
    bool check(string s){
        int count=0;
        for(int i=0; i<s.size(); i++){
            char c=s[i];
            if(c=='(') count++;
            if(c==')') {
                if(count==0)    return false; 
                count--;
            }
        }
        return count==0;
    }
};
